/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.6 Computación pipeline: Código 6.18
* Algoritmo OpenMP con paralelismo implícito para la sustitución progresiva
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void escribir(double *m, double *b,int t, int nodo) {
  int i,j;

  printf("Thread %d:\n", nodo);
  for (i = 0; i < t; i++) {
    for (j = 0; j < t; j++)
      printf("%.4lf * x[%d] %c ", m[i * t + j], j, (j != t - 1) ? '+' : '=');
    printf("%.4lf\n", b[i]);
  }
  printf("\n");
}

void escribirresult(double *m, int t, int nodo){
  int i;

  printf("Thread %d:\n", nodo);
  for (i = 0; i < t; i++)
    printf("%.4lf ", m[i]);
  printf("\n");
}

// Código 6.18

void sp(double *a, double *b, int n, int THREADS) {
    int i, j;
    for (i = 0; i < n; i++) { 
        b[i] = b[i] / a[i * n + i];
        #pragma parallel for private(j)
        for (j = i + 1; j < n; j++)
            b[j] -= a[j * n + i] * b[i];
    }
}

void initializesist(double *m, int t) {
  int i, j;

  for (i = 0; i < t; i++) {
    for (j = 0; j <=i; j++)
      m[i * t + j] = (double)(j + 1);
    for (j = i + 1; j < t; j++)
      m[i * t + j] = 0.;
  }
}

void initializealeasist(double *m, int t) {
  int i, j;

  for (i = 0; i < t; i++) {
    for (j = 0; j <=i; j++)
      m[i * t + j] = 10.*((double)rand() / RAND_MAX);
    for (j = i + 1; j < t; j++)
      m[i * t + j] = 0.;
  }
}

void initializevect(double *m, int t) {
  int i;

  for (i = 0; i < t; i++)
      m[i] = (double)(i + 1);
}

void initializealeavect(double *m, int t){
  int i;

  for (i = 0; i < t; i++)
      m[i] = 10. * ((double)rand() / RAND_MAX);
}

/*
c
c     mseconds - returns elapsed microseconds since Jan 1st, 1970.
c
*/
double mseconds(){
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec * 1000000. + t.tv_usec;
}

int main(int argc, char *argv[]) {
  double start, fin, tiempo, Mflops;
  double *a, *b;
  int THREADS, t, p;

// Ejecución: ejecutable tamañosistema númerothreads

  t = atoi(argv[1]);
  THREADS = atoi(argv[2]);

  omp_set_num_threads(THREADS);

  a = (double *) malloc(sizeof(double) * t * t);
  b = (double *) malloc(sizeof(double) * t);
  initializesist(a, t);
  initializevect(b, t);
#ifdef DEBUG
  escribir(a, b, t, 0);
#endif
  start = mseconds();

  sp(a, b, t, THREADS);

  fin = mseconds();
  tiempo = (fin - start) / 1000000.;

  if (tiempo == 0.) {
    printf("No hay suficiente precision\n");
  } else {
    printf("\n THREADS %d  tamano %ld\n    segundos: %.6lf\n", THREADS, t, tiempo);
#ifdef DEBUG
    escribirresult(b, t, 0);
#endif
  }

  free(a);
  free(b);
}

