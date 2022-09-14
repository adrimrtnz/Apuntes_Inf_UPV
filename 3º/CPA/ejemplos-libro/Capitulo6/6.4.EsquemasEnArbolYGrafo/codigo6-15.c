/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.4 Esquemas en árbol y grafo: Código 6.15
* Ordenación por mezcla en OpenMP
*
* Restricciones: el tamaño de problema es múltiplo del número de threads,
* y el número de threads es potencia de dos
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void escribir(double *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
    printf("%.4lf ", m[i]);
  }
  printf("\n");
}

void mezclar(double *a, int t) {
  int i,j,k;
  double *b = (double *) malloc(sizeof(double) * t * 2);

  i = 0;
  j = t;
  k = 0;
  while(i < t && j < 2 * t) {
    if (a[i] < a[j]) {
      b[k] = a[i];
      i++;
    } else {
      b[k] = a[j];
      j++;
    }
    k++;
  }
  for (; i < t; i++) {
    b[k] = a[i];
    k++;
  }  
  for (; j < 2 * t; j++) {
    b[k] = a[j];
    k++;
  }      
  for (i = 0; i < 2 * t; i++)
    a[i] = b[i];
  free(b);
}

void mergesortsec(double *a, int t) {
  if (t != 1) {
    mergesortsec(a, t / 2);
    mergesortsec(&a[t / 2], t / 2);
    mezclar(a, t / 2);
  }
}
      
void mergesortpar(double *a, int n) {
    int i, tam, THREADS;
    #pragma omp parallel private(i) 
    {
        THREADS = omp_get_num_threads();
        #pragma omp for
// cada thread ordena una parte del array
        for (i = 0; i < THREADS; i++)
            mergesortsec(&a[i * n / THREADS], n / THREADS);
    }
// se realizan las mezclas
    for (tam = n / THREADS, THREADS /= 2; tam < n; tam *= 2, THREADS /= 2)
// para lo que se crea un grupo de threads
// cada vez con menos componentes
        #pragma omp parallel for private(i) shared(THREADS, tam)
        for (i = 0; i < THREADS; i++)
            mezclar(&a[i * tam * 2], tam);
}

void initialize(double *m, int t){
  int i;

  for (i = 0; i < t; i++) {
    m[i] = (double)(i);
  }
}

void initializealea(double *m, int t){
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
  return t.tv_sec * 1000000. + t.tv_usec;
}

int main(int argc, char *argv[]) {
  long int t;
  double start, fin, tiempo, Mflops;
  double *a;

// Ejecución: ejecutable tamañoproblema

  t = atoi(argv[1]);

  a = (double *) malloc(sizeof(double) * t);
   
  initializealea(a, t);
#ifdef DEBUG    
  escribir(a, t);
#endif
  start = mseconds();

  mergesortpar(a, t);

  fin = mseconds();
#ifdef DEBUG
  escribir(a, t);
#endif
  free(a);
}

