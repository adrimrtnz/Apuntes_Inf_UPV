/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.1 Paralelismo de datos: Código 6.1
* Paralelización de la suma de n números con OpenMP
* Paralelismo implícito
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

double suma(double *a, int t) {
  int i;
  double s = 0.;

//Código 6.1

  #pragma omp parallel for reduction(+:s) 
    for (i = 0; i < t; i++) {
      s += a[i];
    }
  return s;
}

void initialize(double *m,int t) {
  int i;

  for (i = 0; i < t; i++) {
    m[i] = (double)(i);
  }
}

void initializealea(double *m, int t){
  int i;

  for (i = 0; i < t; i++) {
      m[i] = (double)rand()/RAND_MAX;
  }
}

void escribir(double *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
    printf("%.4lf ", m[i]);
  }
}
/*
c
c     mseconds - returns elapsed microseconds since Jan 1st, 1970.
c
*/
double mseconds() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec*1000000. + t.tv_usec;
}

int main(int argc, char *argv[]) {
  long int t, iN, fN, incN;
  double start, fin, tiempo, Mflops;
  double *a, s;

  iN = atoi(argv[1]);
  fN = atoi(argv[2]);
  incN = atoi(argv[3]);

  for(t = iN; t <= fN; t += incN) {
    a = (double *) malloc(sizeof(double) * t);
   
    initialize(a, t);

#ifdef DEBUG
    escribir(a, t);
#endif
    start = mseconds();

    s = suma(a, t);

    fin = mseconds();
    tiempo = (fin - start) / 1000000.;

    if (tiempo == 0.) {
      printf("No hay suficiente precision\n");
    } else {
      Mflops = (t / tiempo) / 1000000.;
      printf(" tamano %ld\n    segundos: %.6lf, Mflops: %.6lf\n", t, tiempo, Mflops);
      printf("   suma: %.4lf\n\n",s);
    }

    free(a);
  }
}

