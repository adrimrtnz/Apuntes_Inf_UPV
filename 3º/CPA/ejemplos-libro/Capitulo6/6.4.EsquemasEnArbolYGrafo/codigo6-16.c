/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.4 Esquemas en árbol y grafo: Código 6.16
* Ordenación por mezcla en MPI
*
* Tiene restricciones de tamaños y de numero de procesadores.
* Estas restricciones se pueden quitar como un ejercicio.
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>

#define DISTRIBUCION 10
#define COMBINACION 20

void escribir(double *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
    printf("%.4lf ", m[i]);
  }
  printf("\n");
}

void mezclar(double *a, int t) {
  int i, j, k;
  double *b = (double *) malloc(sizeof(double) * t * 2);

  i = 0;
  j = t;
  k = 0;
  while (i < t && j < 2 * t) {
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

// Código 6.16
      
void distribuir(double *a, int n, int nodo, int np) {
    int des = 1;
    int tam = n / 2;
// se hace una distribución en árbol
    while (tam >= n / np) {
        if (nodo < des)
            MPI_Send(&a[tam], tam, MPI_DOUBLE, nodo + des, DISTRIBUCION, MPI_COMM_WORLD);
        if (nodo >= des && nodo < 2 * des)
            MPI_Recv(a, tam, MPI_DOUBLE, nodo - des, DISTRIBUCION, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        des *= 2;
        tam /= 2;
    }
}

void combinar(double *a, int n, int nodo, int np) {
    int des = np / 2;
    int tam = n / np;
// la combinación se hace en árbol
    while (tam < n) {
        if (nodo >= des && nodo < 2 * des)
        MPI_Send(a, tam, MPI_DOUBLE, nodo - des, COMBINACION, MPI_COMM_WORLD);
        if (nodo < des) {
            MPI_Recv(&a[tam], tam, MPI_DOUBLE, nodo + des, COMBINACION, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
// realizando mezclas los procesos que reciben datos
            mezclar(a, tam);
        }
        des /= 2;
        tam *= 2;
    }
}

void mergesortpar(double *a, int n, int nodo, int np) {
    distribuir(a, n, nodo, np);
    mergesortsec(a, n / np);
    combinar(a, n, nodo, np);
}

void initialize(double *m,i int t) {
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

int main(int argc,char *argv[]) {
  int t;
  int nodo, np;
  int long_name;
  double ti, tf, tiempo, Mflops;
  char    nombre_procesador[MPI_MAX_PROCESSOR_NAME];
  MPI_Status estado;
  double *a;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &nodo);
  MPI_Get_processor_name(nombre_procesador, &long_name);

  t = atoi(argv[1]);

  a = (double *) malloc(sizeof(double) * t);

  if (nodo == 0) {
    initializealea(a, t);
#ifdef DEBUG
    escribir(a, t);
#endif
  }

  MPI_Barrier(MPI_COMM_WORLD);

  ti = MPI_Wtime();

  mergesortpar(a, t, nodo, np);

  MPI_Barrier(MPI_COMM_WORLD);
  tf = MPI_Wtime();

#ifdef DEBUG  
  if (nodo == 0)
    escribir(a, t);
#endif

  free(a);
  
  MPI_Finalize();
}
