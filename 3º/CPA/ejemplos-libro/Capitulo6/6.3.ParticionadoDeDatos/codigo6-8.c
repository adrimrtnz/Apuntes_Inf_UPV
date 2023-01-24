/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.3 Particionado de datos: Código 6.8
* Ordenación por rango con particionado de datos.
*********************************************************************/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ENVIO_FINAL 1

void initialize(int *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
    m[i] = (i * 3) % t;
  }
}

void initializealea(int *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
      m[i] = (int) (10 * ((double)rand() / RAND_MAX));
  }
}

void escribir(int *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
    printf("%d ", m[i]);
  }
  printf("\n");
}

// el array a en el procesador cero contiene inicialmente los datos, 
// que quedarán al final ordenados en él
// n es el número de elementos
// r el array auxiliar donde se calculan los índices
// myid indica en cada proceso su identificador
// numprocs contiene el número total de procesos

void ordenrango(int *a, int n, int *r, int myid, int numprocs) {
    int i, j, k, tl = n / numprocs, *b = NULL;
// se envía el array a desde el proceso cero a todos los demás
    MPI_Bcast(a, n, MPI_INT, 0, MPI_COMM_WORLD);
// cada proceso obtiene el rango de un bloque de elementos
    for (k = 0, i = myid * tl; i < (myid + 1) * tl; i++, k++)
        for (j = 0; j < n; j++)
            if ((a[i] > a[j]) || ((a[i] == a[j]) && (i > j)))
                r[k] = r[k] + 1;
    if (myid == 0) {
// el proceso cero recibe los rangos calculados por todos los procesos
        for (i = 1; i < numprocs; i++)
            MPI_Recv(&r[tl * i], tl, MPI_INT, i, ENVIO_FINAL, 
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        b = (int *) malloc(sizeof(int) * n);
// y obtiene los elementos ordenados
        for (i = 0; i < n; i++)
            b[r[i]] = a[i];
        for (i = 0; i < n; i++)
            a[i] = b[i];
        free(b);
    } else
        MPI_Send(r, tl, MPI_INT, 0, ENVIO_FINAL, MPI_COMM_WORLD);
}

int main( int argc, char *argv[]) {
    int t, iN, fN, incN, tl;
    int *a = NULL, *r = NULL;
    int myid, numprocs;
    double startwtime = 0.0, endwtime, totaltime;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Get_processor_name(processor_name, &namelen);

    iN = atoi(argv[1]);
    fN = atoi(argv[2]);
    incN = atoi(argv[3]);

    for (t = iN; t <= fN; t += incN) {
      tl = t / numprocs;

      if (myid == 0) {
        a = (int *) malloc(sizeof(int) * t);
        r = (int *) calloc(t, sizeof(int));
        initialize(a, t);
#ifdef DEBUG
        printf("Datos de entrada\n");
        escribir(a, t);
#endif
      } else {
        a = (int *) malloc(sizeof(int) * t);
        r = (int *) calloc(tl, sizeof(int));
      }

      MPI_Barrier(MPI_COMM_WORLD);

      startwtime = MPI_Wtime();

      ordenrango(a, t, r, myid, numprocs);

      MPI_Barrier(MPI_COMM_WORLD);

      endwtime = MPI_Wtime();
      totaltime = endwtime - startwtime;
      if (myid == 0) {
        printf("    tiempo de ordenacion= %lf\n", totaltime);
      }

#ifdef DEBUG
      if(myid == 0) {
        printf("Resultado\n");
        escribir(a, t);
      }
#endif  
	       
    free(a);
    free(r);
  }
  MPI_Finalize();

  return 0;
}

            
