/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.3 Paralelismo de datos: Código 6.5
* Ordenación por rango con OpenMP
* Paralelismo explícito
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

//Código 6.5

void rangoparcial(int *a, int *r, int *b, int n, int nodo, int THREADS) {
    int i, j;
    for (i = nodo * n / THREADS; i < (nodo + 1) * n / THREADS; i++) {
        for (j = 0; j < n; j++)
            if ((a[i] > a[j]) || ((a[i] == a[j]) && (i > j)))
                r[i] = r[i] + 1;
        b[r[i]] = a[i];
    }
}

void ordenrango(int *a, int *b, int n, int THREADS) {
    int i, j, *r;
    r = (int *) calloc(n, sizeof(int));
    #pragma omp parallel for private(i) 
    for (i = 0; i < THREADS; i++) 
        rangoparcial(a, r, b, n, i, THREADS);
    free(r);
}

void initialize(int *m,int t) {
  int i;

  for (i = 0; i < t; i++) {
    m[i] = i;
  }
}

void initializealea(int *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
      m[i] = (int) ((10. * rand()) / RAND_MAX);
  }
}

void escribir(int *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
    printf("%d ", m[i]);
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
  int *a, *b;
  int THREADS;

  iN = atoi(argv[1]);
  fN = atoi(argv[2]);
  incN = atoi(argv[3]);
  THREADS = atoi(argv[4]);

  omp_set_num_threads(THREADS);

  for(t = iN; t <= fN; t += incN) {
    a = (int *) malloc(sizeof(int) * t);
    b = (int *) malloc(sizeof(int) * t);
    
    initializealea(a, t);
#ifdef DEBUG    
    escribir(a, t);
#endif
    start = mseconds();

    ordenrango(a, b, t, THREADS);

    fin = mseconds();
    tiempo = (fin - start) / 1000000.;

    if(tiempo == 0.) {
      printf("No hay suficiente precision\n");
    } else {
      printf("\n THREADS %d  tamano %ld\n    segundos: %.6lf\n", THREADS, t, tiempo);
#ifdef DEBUG
      escribir(b, t);
#endif
    }

    free(a);
    free(b);
  }
}

