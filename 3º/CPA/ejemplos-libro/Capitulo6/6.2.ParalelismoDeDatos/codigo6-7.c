/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.3 Paralelismo de datos: Código 6.7
* Multiplicación de matrices con OpenMP
* Paralelismo explícito
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void multmatparcial(double *a, double *b, double *c, int n, int THREADS) {
    int i, j, k;
    double s;
    for (i = 0; i < n / THREADS; i++)
        for (j = 0; j < n; j++) {
            s = 0.;
            for (k = 0; k < n; k++)
                s += a[i * n + k] * b[k * n + j];
            c[i * n + j] = s;
        }
}

void multmat(double *a, double *b, double *c, int n, int THREADS) {
    int i;
    #pragma omp parallel for private(i)
    for (i = 0; i < THREADS; i++) 
        multmatparcial(&a[i * n / THREADS * n], b, &c[i * n / THREADS * n], n, THREADS);
}

void initialize(double *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
    m[i] = i;
  }
}

void initializealea(double *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
      m[i] =(10. * rand()) / RAND_MAX;
  }
}

void escribir(double *m, int t) {
  int i, j;

  for (i = 0; i < t; i++) {
    for(j = 0; j <t; j++)
      printf("%.4lf ", m[i * t + j]);
    printf("\n");
  }
  printf("\n");
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
  long int t, iN, fN, incN;
  double start, fin, tiempo;
  double *a, *b, *c;
  int THREADS;

  iN = atoi(argv[1]);
  fN = atoi(argv[2]);
  incN = atoi(argv[3]);
  THREADS = atoi(argv[4]);

  omp_set_num_threads(THREADS);

  for(t = iN; t <= fN; t += incN) {
    a = (double *) malloc(sizeof(double) * t * t);
    b = (double *) malloc(sizeof(double) * t * t);
    c = (double *) malloc(sizeof(double) * t * t);   
    
    initialize(a, t * t);
    initialize(b, t * t);

#ifdef DEBUG
    escribir(a, t);
    escribir(b, t);
#endif
    start = mseconds();

    multmat(a, b, c, t, THREADS);

    fin = mseconds();
    tiempo = (fin - start) / 1000000.;

    if (tiempo == 0.) {
      printf("No hay suficiente precision\n");
    } else {
      printf("\n THREADS %d  tamano %ld\n    segundos: %.6lf\n", THREADS, t, tiempo);
#ifdef DEBUG
      escribir(c, t);
#endif
    }

    free(a);
    free(b);
    free(c);
  }
}

