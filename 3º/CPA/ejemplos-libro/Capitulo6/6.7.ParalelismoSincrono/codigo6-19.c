/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.7 Paralelismo síncrono: Código 6.19
* Relajación de Jacobi en OpenMP con paralelismo implícito
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

  for (i = 0; i < t * t; i++)
    b[i] = a[i];
}

// la matriz a contiene los datos
// y la b es una matriz auxiliar
void jacobi(double *a, double *b, int n) {
    int i, j;
    double s = 1., tol = 0.01;
    while (s > tol) {
        s = 0.;
// en una iteración se trabaja de a sobre b
        #pragma omp parallel for private(i, j)
        for (i = 1; i < n - 1; i++)
            for (j = 1; j < n - 1; j++)
                b[i * n + j] = (a[(i - 1) * n + j] + a[(i + 1) * n + j] + a[i * n + j - 1] + a[i * n + j + 1]) / 4;
// y en la siguiente de b sobre a
// así se evitan las copias que habría que hacer si se trabajase con
// una única matriz
        #pragma omp parallel for private(i, j)
        for (i = 1; i < n - 1; i++)
            for (j = 1; j < n - 1; j++)
                a[i * n + j] = (b[(i - 1) * n + j] + b[(i + 1) * n + j] + b[i * n + j - 1] + b[i * n + j + 1]) / 4;
// se está evaluando la convergencia cada dos iteraciones
        #pragma omp parallel for private(i, j) reduction(+:s)
        for (i = 1; i < n - 1; i++)
            for (j = 1; j < n - 1; j++)
// en vez de la 1-norma se podría utilizar otra función de distancia
                s += fabs(a[i * n + j] - b[i * n + j]);
    }
}

void initializealea(double *m, int t){
  int i;

  for (i = 0; i < t * t; i++)
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

// Ejecución: ejecutable tamañomalla númerothreads
  t = atoi(argv[1]);
  THREADS = atoi(argv[2]);

  omp_set_num_threads(THREADS);

  a = (double *) malloc(sizeof(double) * (t + 1) * (t + 1));
  b = (double *) malloc(sizeof(double) * (t + 1) * (t + 1));
  initializealea(a, t + 1);
#ifdef DEBUG
  escribir(a, t + 1);
#endif
  copia(a, b, t + 1);

  start = mseconds();

  jacobi(a, b, t + 1);

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

