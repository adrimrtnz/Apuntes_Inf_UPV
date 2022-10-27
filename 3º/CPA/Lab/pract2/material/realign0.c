#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <omp.h>

typedef unsigned char Byte;

// Read a P6 ppm image file, allocating memory
// It returns NULL if there is an error
Byte *read_ppm(char file[],int *width,int *height) {
  FILE *f;
  char tipo[10];
  Byte *a=NULL;
  size_t n;
  f=fopen(file,"rb");
  if (f==NULL) {
    fprintf(stderr,"ERROR: Could not open file \"%s\".\n",file);
  } else {
    fgets(tipo,sizeof(tipo),f);
    if (strcmp(tipo,"P6\n")) {
      fprintf(stderr,"ERROR: \"%s\" should be a PPM of type P6 instead of %s\n",file,tipo);
    } else {
      fscanf(f," #%*[^\n]"); // skip possible comment
      fscanf(f,"%d%d%*d%*c",width,height);
      n=(size_t)*width**height*3;
      a=(Byte*)malloc(n*sizeof(Byte));
      if (a==NULL) {
        fprintf(stderr,"ERROR: Could not allocate memory for %d bytes.\n",(int)n);
      } else{
        fread(a,1,n,f);
      }
    }
    fclose(f);
  }
  return a;
}

// Write image to file
void write_ppm(char file[],int w,int h,Byte *c) {
  FILE *f;
  f=fopen(file,"wb");
  if (f==NULL) {
    fprintf(stderr,"ERROR: Could not create \"%s\".\n",file);
  } else {
    fprintf(f,"P6\n%d %d\n255\n",w,h);
    fwrite(c,h,3*w,f);
    fclose(f);
  }
}

// Compute the difference between two line segments of an image
// a1 and a2 are the two segments. Each of them is n pixels long
// The computation is abandoned if the difference reaches or exceeds c,
// returning the partially computed difference in that case
int distance( int n, Byte a1[], Byte a2[], int c ) {
  int i, d,e;
  n *= 3; // 3 bytes per pixel (red, green, blue)
  d = 0;
  for ( i = 0 ; i < n && d < c ; i++ ) {
    e = (int)a1[i] - a2[i];
    if ( e >= 0 ) d += e; else d -= e;
  }
  return d;
}

// Shift line a, of n pixels, cyclically so that pixel a[p] will go to a[0]
// v is an auxiliary array of min(p,n-p) pixels at least
void cyclic_shift( int n, Byte a[], int p, Byte v[] ) {
  int i,d;

  if ( p != 0 ) {
    n *= 3; p *= 3;
    d = n - p;
    // Shift is done from right to left of from left to right
    // depending on which alternative requires less space in the auxiliary
    // array v
    if ( p <= n / 2 ) { // right to left
      for ( i = 0 ; i < p ; i++ ) v[i] = a[i];
      for ( i = p ; i < n ; i++ ) a[i-p] = a[i];
      for ( i = 0 ; i < p  ; i++ ) a[d+i] = v[i];
    } else { // left to right
      for ( i = 0 ; i < d ; i++ ) v[i] = a[p+i];
      for ( i = p-1 ; i >= 0 ; i-- ) a[i+d] = a[i];
      for ( i = 0 ; i < d  ; i++ ) a[i] = v[i];
    }
  }
}

// Realign the rows of image a, of width w and height h
void realign( int w,int h,Byte a[] ) {
  int y, off,bestoff,dmin,max, d, *voff;
  double t1, t2, t3;
  Byte *v;

  voff = malloc( h * sizeof(int) );
  if ( voff == NULL ) {
    fprintf(stderr,"ERROR: Not enough memory for voff\n");
    return;
  }

  // Part 1. Find optimal offset of each line with respect to the previous line
  t1 = omp_get_wtime();
  for ( y = 1 ; y < h ; y++ ) {

    // Find offset of line y that produces the minimum distance between lines y and y-1
    dmin = distance( w, &a[3*(y-1)*w], &a[3*y*w], INT_MAX ); // offset=0
    bestoff = 0;
    for ( off = 1 ; off < w ; off++ ) {
      d  = distance( w-off, &a[3*(y-1)*w], &a[3*(y*w+off)], dmin );
      d += distance( off, &a[3*(y*w-off)], &a[3*y*w], dmin-d );
      // Update minimum distance and corresponding best offset
      if ( d < dmin ) { dmin = d; bestoff = off; }
    }
    voff[y] = bestoff;
  }
  t1 = omp_get_wtime() - t1;

  // Part 2. Convert offsets from relative to absolute and find maximum offset of any line
  t2 = omp_get_wtime();
  max = 0;
  voff[0] = 0;
  for ( y = 1 ; y < h ; y++ ) {
    voff[y] = ( voff[y-1] + voff[y] ) % w;
    d = voff[y] <= w / 2 ? voff[y] : w - voff[y];
    if ( d > max ) max = d;
  }
  t2 = omp_get_wtime() - t2;

  // Part 3. Shift each line to its place, using auxiliary buffer v
  t3 = omp_get_wtime();
  v = malloc( 3 * max * sizeof(Byte) );
  if ( v == NULL )
    fprintf(stderr,"ERROR: Not enough memory for v\n");
  else {
    for ( y = 1 ; y < h ; y++ ) {
      cyclic_shift( w, &a[3*y*w], voff[y], v );
    }
    free(v);
  }
  t3 = omp_get_wtime() - t3;

  printf("Time (%.2f + %.2f + %.2f) = %.2f\n", t1, t2, t3, t1+t2+t3);

  free(voff);
}

int main(int argc,char *argv[]) {
  char *in, *out = "";
  int   w, h, nh;
  Byte *a;

  if (argc<2) {
    fprintf(stderr,"ERROR: you must provide an input file\n");
    return -1;
  } else if (argc>3) {
    fprintf(stderr,"ERROR: wrong number of arguments\n");
    return -1;
  }
  in = argv[1];               // input filename
  if (argc>2) out = argv[2];  // output filename

  a = read_ppm(in,&w,&h);
  if ( a == NULL ) return 1;

  #pragma omp parallel
  {
    nh = omp_get_num_threads();
  }

  double t = omp_get_wtime();
  realign( w,h,a );
  t = omp_get_wtime() - t;

  printf("Total time in realign function with %d threads: %.2fs\n", nh, t);

  if ( out[0] != '\0' ) write_ppm(out,w,h,a);

  free(a);

  return 0;
}

