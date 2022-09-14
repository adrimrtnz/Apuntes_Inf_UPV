/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.4 Esquemas en árbol y grafo: Código 6.12
* Esquema de la suma prefija en MPI
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>

int sp(int x, int nodo, int np) {
    int des = 1, y;
    while (des < np) {
        if (nodo < np - des)
            MPI_Send(&x, 1, MPI_INT, nodo + des, 10, MPI_COMM_WORLD);
        if (nodo >= des) {
            MPI_Recv(&y, 1, MPI_INT, nodo - des, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            x += y;
        }
        des *= 2;
    }
    return x; 
}

void escribir(int x, int nodo) {
  
  printf("Valor %d en nodo %d\n", x, nodo);
}

int main(int argc,char *argv[]) {
  int nodo, np, x, y;
  int long_name;
  double ti, tf;
  char    nombre_procesador[MPI_MAX_PROCESSOR_NAME];
  MPI_Status estado;
 
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &nodo);
  MPI_Get_processor_name(nombre_procesador, &long_name);

  x = nodo;

  MPI_Barrier(MPI_COMM_WORLD);

  ti = MPI_Wtime();

// EL número de procesos coincide con el número de datos

  y = sp(x, nodo, np);

  MPI_Barrier(MPI_COMM_WORLD);
  tf = MPI_Wtime();
#ifdef DEBUG
  escribir(y, nodo);
#endif
  if (nodo == 0) {
    printf("Proceso %d, %s, Tiempo %.6lf\n", nodo, nombre_procesador, tf - ti);
  }
  
  MPI_Finalize();
}
