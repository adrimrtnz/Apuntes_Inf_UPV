/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.7 Paralelismo síncrono: Código 6.20
* Relajación de Jacobi en OpenMP con paralelismo explícito
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>

void escribir(double *m, int t){
  int i,j;

  for (i = 0; i < t; i++) {
    for (j = 0; j < t; j++)
      printf("%.4lf ", m[i * t + j]);
    printf("\n");
  }
  printf("\n");
}

void copia(double *a, double *b, int t){
  int i;

  for (i = 0; i < t*t; i++)
    b[i] = a[i];
}

void jacobilo(double *a, double *b, double *sp, int n, int nodo, int THREADS) {
    int i, j, tam = (n - 2) / THREADS;
    double s = 1., tol = 0.01;
    while (s > tol) {
        s = 0.;
        sp[nodo] = 0;
        for (i = 1 + nodo * tam; i < 1 + (nodo + 1) * tam; i++)
            for (j = 1; j < n - 1; j++)
                b[i * n + j] = (a[(i - 1) * n + j] + a[(i + 1) * n + j] + a[i * n + j - 1] + a[i * n + j + 1]) / 4;
        #pragma omp barrier
        for (i = 1 + nodo * tam; i < 1 + (nodo + 1) * tam; i++)
            for (j = 1; j < n - 1; j++)
                a[i * n + j] = (b[(i - 1) * n + j] + b[(i + 1) * n + j] + b[i * n + j - 1] + b[i * n + j + 1]) / 4;
        #pragma omp barrier
        for (i = 1 + nodo * tam; i < 1 + (nodo + 1) * tam; i++)
            for (j = 1; j < n - 1; j++)
// cada thread almacena en una posición de sp su contribución 
// a la función de distancia
                sp[nodo] += fabs(a[i * n + j] - b[i * n + j]);
        #pragma omp barrier
        #pragma omp single
        {
            for (i = 0; i < THREADS; i++)
                s += sp[i];
            for (i = 0; i < THREADS; i++)
                sp[i] = s;
        }  
        s = sp[nodo];
    }
}

void jacobi(double *a, double *b, int n, int THREADS) {
    int i;
    double *s;
    s = (double *) malloc(sizeof(double) * THREADS);
    #pragma omp parallel for private(i)
    for (i = 0; i < THREADS; i++)
        jacobilo(a, b, s, n, i, THREADS);
    free(s);
}

void initializealea(double *m, int t){
  int i;

  for (i = 0; i < t*t; i++)
    m[i] = 10.*((double)rand()/RAND_MAX);
}

/*
c
c     mseconds - returns elapsed microseconds since Jan 1st, 1970.
c
*/
double mseconds() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec * 1000000. + t.tv_usec;
}

int main(int argc, char *argv[]) {
  double start, fin, tiempo, Mflops;
  double *a, *b;
  int THREADS, t, p;

  t = atoi(argv[1]);
  THREADS = atoi(argv[2]);

  omp_set_num_threads(THREADS);
  printf("THREADS %d\n", THREADS);
  a = (double *) malloc(sizeof(double) * (t + 1) * (t + 1));
  b = (double *) malloc(sizeof(double) * (t + 1) * (t + 1));
  initializealea(a, t + 1);
#ifdef DEBUG
  escribir(a, t + 1);
#endif
  copia(a, b, t + 1);

  start = mseconds();

  jacobi(a, b, t + 1, THREADS);

  fin = mseconds();
  tiempo = (fin - start) / 1000000.;

  if (tiempo == 0.) {
    printf("No hay suficiente precision\n");
  } else {
    printf("\n THREADS %d  tamano %ld\n    segundos: %.6lf\n", THREADS, t, tiempo);
#ifdef DEBUG
    escribir(a, t + 1);
#endif
  }

  free(a);
  free(b);
}

