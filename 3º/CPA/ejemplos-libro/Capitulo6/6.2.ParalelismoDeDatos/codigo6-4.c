/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.3 Paralelismo de datos: Código 6.4
* Ordenación por rango con OpenMP
* Paralelismo implícito
* y un único grupo de threads esclavos
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void ordenrango(int *a, int *b, int n) {
  int i, j, *r;
  
  r = (int *) calloc(n, sizeof(int));

//Código 6.4

    #pragma omp parallel for private(i, j)
// cada threads calcula el rango de un conjunto de elementos
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            if ((a[i] > a[j]) || ((a[i] == a[j]) && (i > j)))
                r[i] = r[i] + 1;
// y pone el elemento en la posición correspondiente en el array destino
        b[r[i]] = a[i];
    }
}

void initialize(int *m, int t) {
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

  iN = atoi(argv[1]);
  fN = atoi(argv[2]);
  incN = atoi(argv[3]);

  for(t = iN; t <= fN; t += incN) {
    a = (int *) malloc(sizeof(int) * t);
    b = (int *) malloc(sizeof(int) * t);
    
    initializealea(a, t);
#ifdef DEBUG    
    escribir(a, t);
#endif
    start = mseconds();

    ordenrango(a, b, t);

    fin = mseconds();
    tiempo = (fin - start) / 1000000.;

    if (tiempo == 0.) {
      printf("No hay suficiente precision\n");
    } else {
      printf("\n tamano %ld\n    segundos: %.6lf\n", t, tiempo);
#ifdef DEBUG      
      escribir(b, t);
#endif      
    }

    free(a);
    free(b);
  }
}

