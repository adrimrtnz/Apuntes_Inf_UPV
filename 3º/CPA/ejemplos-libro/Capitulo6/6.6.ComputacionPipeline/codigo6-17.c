/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.6 Computación pipeline: Código 6.17
* Algoritmo de paso de mensajes en MPI para la sustitución progresiva
*
* Con un proceso por ecuación.
* En el libro se proponen modificaciones para eliminar esta restricción,
* y el ejercicio 6.17 propone el estudio experimental de esas modificaciones.
*********************************************************************/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ENVIO 10

void initializealea(double *m, int t, int nodo) {
  int i;
  for (i = 0; i <= nodo; i++)
    m[i] = 10 * ((double)rand() / RAND_MAX);
  for (i = nodo + 1; i < t; i++)
    m[i] = 0.;
}

int initialize(double *m, int t, int nodo) {
  int i;
  for (i = 0; i <= nodo; i++)
    m[i] = i + 1;
  for (i = nodo + 1; i < t; i++)
    m[i] = 0.;
}

void escribir(double *m, int t, double b, int nodo) {
  int i;

  printf("En proceso : %d\n", nodo);
  for (i = 0; i < t; i++) {
    printf("%.4lf * x[%d] %c ", m[i], i, (i != t - 1) ? '+' : '=');
  }
  printf("%.4lf\n", b);
}

// el número de procesos coincide con el de filas de la matriz a
// el proceso i almacena la fila i de la matriz a 
// y el elemento i del vector b
double sp(double *a, int n, double b, int myid) {
    int i;
    double x, r = 0;
    if (myid == 0) {
        x = b / a[0];
        MPI_Send(&x, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    }
    if (myid == (n - 1)) {
        for (i = 0; i < n - 1; i++) {
            MPI_Recv(&x, 1, MPI_DOUBLE, n - 2, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            r += a[i] * x;
        }
        x = (b - r) / a[n - 1];
    }
    if ((myid != 0) && (myid != n - 1)) {
        for (i = 0; i < myid; i++) {
            MPI_Recv(&x, 1, MPI_DOUBLE, myid - 1, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&x, 1, MPI_DOUBLE, myid + 1, i, MPI_COMM_WORLD);
            r += a[i] * x;
        }
        x = (b - r) / a[myid];
        MPI_Send(&x, 1, MPI_DOUBLE, myid + 1, myid, MPI_COMM_WORLD);
    }
    return x;
}

int main( int argc, char *argv[]) {
    double *a, b, x;
    int myid, numprocs;
    double startwtime = 0.0, endwtime, totaltime;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Get_processor_name(processor_name, &namelen);
    a = (double *) malloc(sizeof(double) * numprocs);
    initialize(a, numprocs, myid);
    b = myid + 1;
    escribir(a, numprocs, b, myid);

    MPI_Barrier(MPI_COMM_WORLD);

    startwtime = MPI_Wtime();
    
    x = sp(a, numprocs, b, myid);

    MPI_Barrier(MPI_COMM_WORLD);

    endwtime = MPI_Wtime();
    totaltime = endwtime - startwtime;
    if (myid == 0) {
      printf("    tiempo= %lf\n", totaltime);
    }

    printf("variable %d: %.4lf\n", myid, x);
    free(a);

  MPI_Finalize();
  return 0;
}

            

