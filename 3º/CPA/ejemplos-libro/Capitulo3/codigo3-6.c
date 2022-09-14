/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 3, Código 3.6
* Programa "saludo" en MPI utilizando primitivas send/receive
*********************************************************************/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int myrank, size, origen, destino, tag = 1;
    char mensaje[100];

    MPI_Status status;
    MPI_Init(&argc, &argv);                  // Inicializa el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);  // Número de identificación 
                                             // del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size);    // Número total de procesos

    if (myrank != 0) {
        printf("Proceso %d de %d\n", myrank, size);
        sprintf(mensaje,"Saludos desde el proceso %d!", myrank);
        destino = 0;
        MPI_Send(mensaje, strlen(mensaje)+1, MPI_CHAR, destino, tag, MPI_COMM_WORLD);
    } else {
        printf("proceso 0, total procesos = %d ", size);
        for (origen = 1; origen < size; origen++) {
          MPI_Recv(mensaje, 100, MPI_CHAR, origen, tag,  MPI_COMM_WORLD, &status); 
          printf("%s\n", mensaje);
        }
    }

    MPI_Finalize();
}
