/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.4 Esquemas en árbol y grafo: Código 6.14
* Obtención de los datos a enviar y recibir para reducir el coste de las comunicaciones
* en un algoritmo de cálculo de clases de equivalencia por paso de mensajes.
* Este método se puede utilizar para implementar un algoritmo MPI
* en el que se comunican sólo los datos que son necesarios (ejercicio 6.11)
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DAT 12
#define PROC 2

void iniciar(int *pd) {
  pd[0] = 1;
  pd[1] = 1;
  pd[2] = 4;
  pd[3] = 7;
  pd[4] = 1;
  pd[5] = 11;
  pd[6] = 6;
  pd[7] = 8;
  pd[8] = 10;
  pd[9] = 6;
  pd[10] = 4;
  pd[11] = 6;
}

void escribir(int nodo, int *ne, int *nr, int e[PROC][DAT / PROC], int r[PROC][DAT / PROC]){
  int i, j;

  printf("nodo %d:\n", nodo);
  for (i = 0; i < PROC; i++)
    if(i != nodo) {
      printf("  envios a %d, %d:", i, ne[i]);
      for (j = 0; j < ne[i]; j++)
        printf(" %d ", e[i][j]);
      printf("\n");
      printf("  recepciones de %d, %d:", i, nr[i]);
      for (j = 0; j < nr[i]; j++)
        printf(" %d ", r[i][j]);
      printf("\n");
    }
}

void obtenerenvrec(int n, int *pd) {
  int i, j, ne[PROC], nr[PROC], e[PROC][DAT / PROC], r[PROC][DAT / PROC];

  for (i = 0; i < PROC; i++) {
    ne[i] = 0;
    nr[i] = 0;
    for (j = 0; j < DAT / PROC; j++) {
      e[i][j] = 0;
      r[i][j] = 0;
    }
  }
  escribir(n, ne, nr, e, r);
  for (i = n * DAT / PROC; i < (n + 1) * DAT / PROC; i++)
    if (pd[i] / (DAT / PROC) != n) {
      r[pd[i] / (DAT / PROC)][nr[pd[i] / (DAT / PROC)]] = i;
      nr[pd[i] / (DAT / PROC)]++;
    } 
  escribir(n, ne, nr, e, r);
  for (i = 0; i < DAT; i++)
    if (i / (DAT / PROC) != n)
      if (pd[i] / (DAT / PROC) == n) {
        e[i / (DAT / PROC)][ne[i / (DAT / PROC)]] = pd[i];
        ne[i / (DAT / PROC)]++;
      }
  escribir(n, ne, nr, e, r);
}

int main(int argc, char *argv[]) {
  int pd[DAT], nodo;

  iniciar(pd);

  for (nodo = 0; nodo < PROC; nodo++)
    obtenerenvrec(nodo, pd); 
}
