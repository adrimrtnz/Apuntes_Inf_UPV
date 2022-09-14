/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.2 Paralelismo de datos: Código 6.2
* Paralelización de la suma de n números con OpenMP
* Paralelismo explícito
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void sumaparcial(double *a, int n) {
    int i;
    double s = 0;
    for (i = 0; i < n; i++)
      s += a[i];
    a[0] = s;
}

double sumatotal(double *a, int n, int THREADS) {
    int i;
    double s = 0.;
    for (i = 0; i < n; i += n/THREADS)
        s += a[i];
    return s;
}

// a es el array donde están los datos
// n el número de datos
// THREADS el número de threads que intervienen en la computación
double suma(double *a, int n, int THREADS) {
    int i;
    #pragma omp parallel for private(i)
// todos los threads realizan sumas parciales
// Suponemos que el tamaño del problema (n) es múltiplo del número de threads (THREAS)
// Lo mismo ocurre en otros ejemplos de este capítulo
// En el primer problema del capítulo se propone quitar estas restricciones
    for (i = 0; i < THREADS; i++) 
      sumaparcial(&a[i * n / THREADS], n / THREADS);	
// y el mestro acumula los resultados parciales
    return sumatotal(a, n, THREADS);
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
  int THREADS;

  iN = atoi(argv[1]);
  fN = atoi(argv[2]);
  incN = atoi(argv[3]);
  THREADS = atoi(argv[4]);

  omp_set_num_threads(THREADS);

  for(t = iN; t <= fN; t += incN) {
    a = (double *) malloc(sizeof(double) * t);
   
    initialize(a, t);

#ifdef DEBUG
    escribir(a, t);
#endif
    start = mseconds();

    s = suma(a, t, THREADS);

    fin = mseconds();
    tiempo = (fin - start) / 1000000.;

    if (tiempo == 0.) {
      printf("No hay suficiente precision\n");
    } else {
      Mflops = (t / tiempo) / 1000000.;
      printf("\n THREADS %d  tamano %ld\n    segundos: %.6lf, Mflops: %.6lf\n", THREADS, t, tiempo, Mflops);
        printf("   suma: %.4lf\n\n", s);
    }

    free(a);
  }
}

