/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.10 Trabajadores replicados: Códigos 6.27 y 6.28
* Solución del problema de las reinas utilizando bolsa de tareas en MPI
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <mpi.h>

#define N 12

#define MAE_TRA 1
#define TRA_MAE 2

struct nodo {
  int t[N + 1];
  struct nodo *sig;
};

void copia(int *a, int *b, int t){
  int i;

  for (i = 0; i < t; i++)
    b[i] = a[i];
}

void iniciar(struct nodo **d) {
  int i;

  *d = (struct nodo *) malloc(sizeof(struct nodo));
  
  for (i = 0; i < N; i++)
    (*d)->t[i] = -1;
  (*d)->t[N] = 0;
  (*d)->sig = NULL;
}

void ponerreina(int *tareaact, int pos, int col) {
  tareaact[pos] = col;
  tareaact[N] = pos + 1;
}

void escribirtarea (int *tareaact) {
  int i;

  for (i = 0; i < tareaact[N]; i++)
    printf("%d ", tareaact[i]);
  printf("+");
}

void insertar(struct nodo **d, int *nuevatarea) {
  struct nodo *temp;
  int i;

  temp = (struct nodo *) malloc(sizeof(struct nodo));
  for (i = 0; i < N + 1; i++)
    temp->t[i] = nuevatarea[i];
  temp->sig = (*d);
  (*d) = temp;
}

void extraer(struct nodo **d, int *tareaact) {
  struct nodo *p;
  int i;

  for (i = 0; i < N + 1; i++)
    tareaact[i] = (*d)->t[i];
  p = (*d);
  (*d) = (*d)->sig;
  free(p);
}

int valido(int *tareaact,int col) {
  int i;

  for (i = 0; i < tareaact[N]; i++)
    if (tareaact[i]==col || tareaact[N]+col==tareaact[i]+i || col-tareaact[N]==tareaact[i]-i)
      return 0;
  return 1;
}

void escribir(struct nodo *d) {
  int i;

  while (d != NULL) {
    escribirtarea(d->t);
    d = d->sig;
  }
  printf("*\n");
}

void escribirmensaje(int *m) {
  int i;

  printf("reinas ");
  for (i = 0; i < m[N]; i++)
    printf("%d ", m[i]);
  printf(", fila %d", m[N]);
  printf(", Soluciones %d, ", m[N+1]);
  for (i = N + 2; i < N + 2 + m[N + 1]; i++)
    printf("%d ", m[i]);
  printf(" , procesador %d\n", m[2 * N + 2]);
}

void escribirtarea1(int *m) {
  int i;

  printf("reinas ");
  for (i = 0; i < m[N]; i++)
    printf("%d ", m[i]);
  printf(", fila %d\n", m[N]);
}

void reinas(int nodo, int np) {
  struct nodo *bolsa;
  int tareaact[N + 1];
  int i, j, tareas, trabajadores, acabados, fin, *esperando;
  int mensaje[2 * N + 3];
  MPI_Status *estado = NULL;
 
  if (nodo == 0) {
    esperando = (int *) malloc(sizeof(int)*np);
    for (i = 1; i < np; i++)
      esperando[i] = 1;
    iniciar(&bolsa);
#ifdef DEBUG
    escribir(bolsa);
#endif
    tareas = 1;
    trabajadores = np - 1;
    acabados = 0;
    fin = 0;
    while (!fin) {
      MPI_Recv(mensaje, 2 * N + 3, MPI_INT, MPI_ANY_SOURCE, TRA_MAE, MPI_COMM_WORLD, estado);
#ifdef DEBUG
      printf("Maestro recibe :");
      escribirmensaje(mensaje);
#endif
      copia(mensaje, tareaact, N - 1);
      acabados++;
      esperando[mensaje[2 * N + 2]] = 1;
      if (mensaje[N] == N-1) {
        for (i= N + 2; i < N + 2 + mensaje[N + 1]; i++) {
          ponerreina(tareaact, mensaje[N], mensaje[i]);
          printf("Solucion: ");
          escribirtarea(tareaact);
          printf("\n--------\n");
        }
      } else {
        tareas += mensaje[N + 1];
        for (i = N + 2; i < N + 2 + mensaje[N + 1]; i++) {
#ifdef DEBUG
          escribirtarea1(tareaact);
          printf("%d %d\n", mensaje[N], mensaje[i]);
#endif
          ponerreina(tareaact, mensaje[N], mensaje[i]);
#ifdef DEBUG
          escribirtarea1(tareaact);
#endif
          insertar(&bolsa, tareaact);
#ifdef DEBUG
          escribir(bolsa);
#endif
        }
      }
      for (i = 1; i <np; i++) { 
        if (esperando[i] && tareas) {
          extraer(&bolsa, tareaact);
#ifdef DEBUG
          escribir(bolsa);
          printf("Maestro envia :");
          escribirtarea1(tareaact);
#endif
          MPI_Send(tareaact, N + 1, MPI_INT, i, MAE_TRA, MPI_COMM_WORLD);
          tareas--;
          esperando[i]=0;
          acabados--;
        }
      }
      fin = (acabados == trabajadores && tareas == 0);
    }
    tareaact[N] = -1;
    for (i = 1; i <np; i++)
      MPI_Send(tareaact, N + 1, MPI_INT, i, MAE_TRA, MPI_COMM_WORLD);
    free(esperando);
  } else {
    mensaje[N + 1] = 0;
    mensaje[N] = 0;
    mensaje[2 * N + 2] = nodo;
#ifdef DEBUG
    printf("proceso %d envia: ", nodo);
    escribirmensaje(mensaje);
#endif
    MPI_Send(mensaje, 2 * N + 3, MPI_INT, 0, TRA_MAE, MPI_COMM_WORLD);
    MPI_Recv(mensaje, N + 1, MPI_INT, 0, MAE_TRA, MPI_COMM_WORLD, estado);
#ifdef DEBUG
    printf("proceso %d recibe: ", nodo);
    escribirtarea1(mensaje);
#endif    
    while (mensaje[N] != -1) {
      mensaje[N + 1] = 0;
      for (i = 0; i < N; i++) {
        if (valido(mensaje, i)) {
          mensaje[N + 1]++;
          mensaje[N + 1 + mensaje[N + 1]] = i;
        }
      }
      MPI_Send(mensaje, 2 * N + 3, MPI_INT, 0, TRA_MAE, MPI_COMM_WORLD);
#ifdef DEBUG
      printf("proceso %d envia: ", nodo);
      escribirmensaje(mensaje);
#endif
      MPI_Recv(mensaje, N + 1, MPI_INT, 0, MAE_TRA, MPI_COMM_WORLD, estado);
    }
  }
}

int main(int argc, char *argv[]) {
  int nodo, np;
  int long_name;
  double ti, tf;
  char    nombre_procesador[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &nodo);
  MPI_Get_processor_name(nombre_procesador, &long_name);

  MPI_Barrier(MPI_COMM_WORLD);

  ti = MPI_Wtime();

  reinas(nodo, np);

  MPI_Barrier(MPI_COMM_WORLD);
  tf = MPI_Wtime();
  if (nodo == 0)
    printf("Proceso %d, %s, Tiempo %.6lf\n", nodo, nombre_procesador, tf - ti);

  MPI_Finalize();
}

