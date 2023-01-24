/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.3 Particionado de datos: Código 6.9
* Ordenación por rango con particionado de datos,
* con los datos inicialmente distribuidos en el sistema
*********************************************************************/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ENVIO_FINAL 1
#define ENVIO_INTERMEDIO 2

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

void ordenrangolocal(int *a, int *b, int *r, int t, int n, int myid, int paso) {
    int i, j;
    for (i = 0; i < t; i++)
        for (j = 0; j < t; j++)
            if ((a[i] > b[j]) || ((a[i] == b[j]) && ((i + t * myid) > ((j + t * myid + paso* t ) % n))))
                r[i] = r[i] + 1;
}

// a contiene los elementos, en el proceso cero quedarán ordenados
// b es un array auxiliar
// r el array de rangos en cada proceso
// rt el array de todos los rangos en el proceso cero

void ordenrango(int *a, int *b, int *r, int *rt, int n, int myid, int numprocs) {
    int i, j, k, tl = n / numprocs, paso, origen, destino;
    origen = myid + 1;
    destino = myid - 1;
    if (myid == 0)    destino = numprocs - 1;
    if (myid == numprocs - 1)    origen = 0;
// los datos están distribuidos en el sistema
// cada proceso tiene una parte de los elementos en su array local a
// que se copia en b para comparar elementos de a con los de b
    for (i = 0; i < tl; i++)    b[i] = a[i];
    ordenrangolocal(a, b, r, tl, n, myid, 0);
// en cada paso
    for (paso = 1; paso < numprocs; paso++) {
// cada proceso envía a su izquierda
        MPI_Send(b, tl, MPI_INT, destino, ENVIO_INTERMEDIO, MPI_COMM_WORLD);
// y recibe de su derecha (cíclicamente)
        MPI_Recv(b, tl, MPI_INT, origen, ENVIO_INTERMEDIO, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        ordenrangolocal(a, b, r, tl, n, myid, paso);
    }
    if (myid == 0) {
        for (i = 0; i< tl; i++)
            rt[i] = r[i];
        for (i = 1; i < numprocs; i++) {
// el proceso cero recibe de los demás los rangos locales
            MPI_Recv(&rt[tl * i], tl, MPI_INT, i, ENVIO_FINAL, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
// y en el array b los elementos a ordenar
            MPI_Recv(&b[tl * i], tl, MPI_INT, i, ENVIO_FINAL, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
// y obtiene los elementos ordenados en a
        for (i = 0; i < n; i++)
          a[rt[i]] = b[i];
    } else {
        MPI_Send(r, tl, MPI_INT, 0, ENVIO_FINAL, MPI_COMM_WORLD);
        MPI_Send(a, tl, MPI_INT, 0, ENVIO_FINAL, MPI_COMM_WORLD);
    }
}

int main(int argc, char *argv[]) {
    int t, iN, fN, incN, tl;
    int *a = NULL, *r = NULL, *b = NULL, *rt = NULL;
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

    for(t = iN; t <= fN; t += incN) {
      tl = t / numprocs;

      if (myid == 0) {
        a = (int *) malloc(sizeof(int) * t);
        r = (int *) calloc(tl, sizeof(int));
        b = (int *) malloc(sizeof(int) * t);
        rt = (int *) calloc(t, sizeof(int));
        initialize(a, tl);
#ifdef DEBUG
        printf("Datos de entrada en %d\n", myid);
        escribir(a, tl);
#endif
      } else {
        a = (int *) malloc(sizeof(int) * tl);
        r = (int *) calloc(tl, sizeof(int));
        b = (int *) malloc(sizeof(int) * tl);
        initialize(a, tl);
#ifdef DEBUG
        printf("Datos de entrada en %d\n", myid);
        escribir(a, tl);
#endif     
      }

      MPI_Barrier(MPI_COMM_WORLD);

      startwtime = MPI_Wtime();

      ordenrango(a, b, r, rt, t, myid, numprocs);

      MPI_Barrier(MPI_COMM_WORLD);

      endwtime = MPI_Wtime();
      totaltime = endwtime - startwtime;
      if (myid == 0) {
        printf("    tiempo de ordenacion= %lf\n", totaltime);
      }

#ifdef DEBUG
      if (myid==0) {
        printf("Resultado\n");
        escribir(a, t);
      }
#endif  
	       
    free(a);
    free(b);
    free(r);
    free(rt);
  }
  MPI_Finalize();

  return 0;
}

            

