/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.7 Paralelismo síncrono: Código 6.21
* Relajación de Jacobi en MPI
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <mpi.h>

#define ENVIOINI 1
#define ENVIOFIN 2
#define ENVIOMAS 3
#define ENVIOMENOS 4
#define ENVIOACUM 5
#define ENVIODIF 6

#define TOLERANCIA 0.001

void escribir(double *m, int fm, int cm){
  int i, j;

  for (i = 0; i < fm; i++) {
    for (j = 0; j < cm; j++)
      printf("%.0lf ",m[i * cm + j]);
    printf("\n");
  }
  printf("\n");
}

void copia(double *a, double *b, int t){
  int i;

  for (i = 0; i < t; i++)
    b[i] = a[i];
}

void envioini(double *a, int t, int tl, int nodo, int np) {
  int i;
  MPI_Status *estado = NULL;

  if (nodo == 0)
    for (i = 1; i < np; i++)
      MPI_Send(&a[(tl - 2) * i * t], tl * t, MPI_DOUBLE, i, ENVIOINI, MPI_COMM_WORLD);
  else
    MPI_Recv(a, tl * t, MPI_DOUBLE, 0, ENVIOINI, MPI_COMM_WORLD, estado);
}

void recepcionfin(double *a, int t, int tl, int nodo, int np) {
  int i;
  MPI_Status *estado = NULL;

  if (nodo == 0)
    for (i = 1; i < np; i++)
      MPI_Recv(&a[(1 + (tl - 2) * i) * t], (tl - 2) * t, MPI_DOUBLE, i, ENVIOFIN, MPI_COMM_WORLD, estado);
  else
    MPI_Send(&a[t], (tl - 2) * t, MPI_DOUBLE, 0, ENVIOFIN, MPI_COMM_WORLD);
}

void envio(double *a, int n, int tl, int nodo, int np) {
    if (nodo < np - 1)
        MPI_Send(&a[(tl - 2) * n + 1], n - 2, MPI_DOUBLE, nodo + 1, ENVIOMAS, MPI_COMM_WORLD);
    if (nodo > 0) {
        MPI_Send(&a[n + 1], n - 2, MPI_DOUBLE, nodo - 1, ENVIOMENOS, MPI_COMM_WORLD);
        MPI_Recv(&a[1], n - 2, MPI_DOUBLE, nodo - 1, ENVIOMAS, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    if (nodo < np - 1)
        MPI_Recv(&a[(tl - 1) * n + 1], n - 2, MPI_DOUBLE, nodo + 1, ENVIOMENOS, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

double norma(double s, int nodo, int np) {
  int i;
  double sl = 0.;
  MPI_Status *estado = NULL;

  if (nodo == 0) {
    for (i = 1; i < np; i++) {
      MPI_Recv(&sl, 1, MPI_DOUBLE, i, ENVIOACUM, MPI_COMM_WORLD, estado);
      s += sl;
    }
    for (i = 1; i <np; i++)
      MPI_Send(&s, 1, MPI_DOUBLE, i, ENVIODIF, MPI_COMM_WORLD);
  } else { 
    MPI_Send(&s, 1, MPI_DOUBLE, 0, ENVIOACUM, MPI_COMM_WORLD);
    MPI_Recv(&s, 1, MPI_DOUBLE, 0, ENVIODIF, MPI_COMM_WORLD, estado);
  }
  return sqrt(s);
}

void jacobipar(double *a, double *b, int n, int tl, int nodo, int np) {
    int i, j, N = n - 2, Nl = tl - 2;
    double s = 1., tol = 0.01;
    envioini(a, n, tl, nodo, np);  
    copia(a, b, tl * n);
    while (s > tol) {
        s = 0.;
        for (i = 1; i <= Nl; i++)
            for (j = 1; j <= N; j++)
                b[i * n + j] = (a[(i - 1) * n + j] + a[(i + 1) * n + j] + a[i * n + j - 1] + a[i * n + j + 1]) / 4;
        envio(b, n, tl, nodo, np);
        for (i = 1; i <= Nl; i++)
            for(j = 1; j <= N; j++)
                a[i * n + j] = (b[(i - 1) * n + j] + b[(i + 1) * n + j] + b[i * n + j - 1] + b[i * n + j + 1]) / 4;
        envio(a, n, tl, nodo, np);
        for (i = 1; i <= Nl; i++)
            for (j = 1; j <= N; j++)
                s += fabs(a[i * n + j] - b[i * n + j]);
        s = norma(s, nodo, np);
    }
    recepcionfin(a, n, tl, nodo, np);
}

void jacobisec(double *a, double *b, int t) {
  int i, j, N = t - 2;
  double s = 1., tol = 0.01;

  while(s > tol) {
    s = 0.;
    for (i = 1; i <= N; i++)
      for (j = 1; j <=N; j++)
        b[i * t + j] = (a[(i - 1) * t + j] + a[(i + 1) * t + j] + a[i * t + j - 1] + a[i * t + j + 1]) / 4;
    for (i = 1; i <= N; i++)
      for (j = 1; j <= N; j++)
        a[i * t + j] = (b[(i - 1) * t + j] + b[(i + 1) * t + j] + b[i * t + j - 1] + b[i * t + j + 1]) / 4;
    for (i = 1; i <=N; i++)
      for (j = 1; j <=N; j++)
        s += pow(fabs(a[i * t + j] - b[i * t + j]), 2);
    s = sqrt(s);
  }
}

void initializealea(double *m, int t) {
  int i;

  for (i = 0; i < t * t; i++)
    m[i] = 10. * ((double)rand() / RAND_MAX);
}

void comparar(double *a, double *b, int t) {
  int i;

  for (i = 0; i < t * t; i++)
    if (fabs(a[i] - b[i]) > TOLERANCIA) {
      printf("Diferencia en %d: %.12lf , %.12lf\n", i, a[i], b[i]);
      return;
    }
}

int main(int argc, char *argv[]) {
  int nodo, np, t, tl, N;
  int long_name;
  double ti, tf;
  double *a, *b, *a0, *b0;
  char    nombre_procesador[MPI_MAX_PROCESSOR_NAME];
  MPI_Status estado;
 
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &nodo);
  MPI_Get_processor_name(nombre_procesador, &long_name);

  if (nodo == 0) {
    N = atoi(argv[1]);
  }
  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
 
  t = N + 2;
  tl = N / np + 2;
  if (nodo == 0) {
    a = (double *) malloc(sizeof(double) * t * t);
    b = (double *) malloc(sizeof(double) * t * t);
    a0 = (double *) malloc(sizeof(double) * t * t);
    b0 = (double *) malloc(sizeof(double) * t * t);
  } else {
    a = (double *) malloc(sizeof(double) * tl * t);
    b = (double *) malloc(sizeof(double) * tl * t);
  }
  
  if (nodo == 0) {
    initializealea(a, t);
    copia(a, b, t * t);
    copia(a, a0, t * t);
    copia(a, b0, t * t);
    jacobisec(a0, b0, t);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  ti = MPI_Wtime();

  jacobipar(a, b, t, tl, nodo, np);

  MPI_Barrier(MPI_COMM_WORLD);
  tf = MPI_Wtime();
  if (nodo == 0) {
    printf("Proceso %d, %s, Tiempo %.6lf\n", nodo, nombre_procesador, tf - ti);
// Comprueba que el resultado secuencial y el paralelo coinciden
    comparar(a0, a, t);
  }

  MPI_Finalize();
  free(a);
  free(b);
  if (nodo == 0) {
    free(a0);
    free(b0);
  }
}

