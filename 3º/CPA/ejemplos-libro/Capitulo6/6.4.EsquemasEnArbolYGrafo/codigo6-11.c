/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.4 Esquemas en árbol y grafo: Código 6.11
* Esquema de la suma prefija en OpenMP
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void escribir(double *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
    printf("%.4lf ",m[i]);
  }
  printf("\n");
}

void sumapref(double *a, int n) {
    int i, des = 1;
    double *b;
    b = (double *) malloc(sizeof(double) * n);
    #pragma omp parallel private(i, des)
    {
        i = omp_get_thread_num();
        des = 1;
        while (des < n) {
            if (i < n - des)
                b[i + des] = a[i];
            #pragma omp barrier
            if (i >= des)
                a[i] += b[i];
            #pragma omp barrier
                des *= 2;
        }
    }
    free(b);
}

void initialize(double *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
    m[i] = (double)(i);
  }
}

void initializealea(double *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
      m[i] = (double)rand() / RAND_MAX;
  }
}

/*
c
c     mseconds - returns elapsed microseconds since Jan 1st, 1970.
c
*/
double mseconds(){
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec*1000000. + t.tv_usec;
}

int main(int argc, char *argv[]) {
  long int t, iN, fN, incN;
  double start, fin, tiempo, Mflops;
  double *a;

// Ejecución: ejecutable tamañoinicial tamañofinal incremento

  iN = atoi(argv[1]);
  fN = atoi(argv[2]);
  incN = atoi(argv[3]);

  for(t = iN; t <= fN; t += incN) {
    a = (double *) malloc(sizeof(double) * t);
   
    initialize(a, t);
#ifdef DEBUG    
    escribir(a, t);
#endif

// Se ponen en marcha tantos threads como elementos tenga el array
    omp_set_num_threads(t);

    start = mseconds();

    sumapref(a, t);

    fin = mseconds();

#ifdef DEBUG    
    escribir(a, t);
#endif
    free(a);
  }
}

