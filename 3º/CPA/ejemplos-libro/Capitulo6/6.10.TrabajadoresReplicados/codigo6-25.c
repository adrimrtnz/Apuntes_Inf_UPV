/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.10 Trabajadores replicados: Código 6.25
* Solución secuencial del problema de las reinas utilizando bolsa de tareas
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 6

struct tarea {
  int s[N];
  int fila;
};

struct nodo {
  struct tarea t;
  struct nodo *sig;
};

void iniciar(struct nodo **d) {
  int i;

  *d = (struct nodo *) malloc(sizeof(struct nodo));
  
  for (i = 0; i < N; i++)
    (*d)->t.s[i] = -1;
  (*d)->t.fila = 0;
  (*d)->sig = NULL;
}

void escribirtarea (struct tarea tareaact) {
  int i;

  for (i = 0; i < tareaact.fila; i++)
    printf("%d ", tareaact.s[i]);
  printf("+");
}

void escribir(struct nodo *d) {
  int i;

  while (d != NULL) {
    escribirtarea(d->t);
    d = d->sig;
  }
  printf("*\n");
}

int vacia(struct nodo *d) {
  return d == NULL;
}

struct tarea extraer(struct nodo **d) {
  struct tarea tareaact;
  struct nodo *p;
  int i;

  for (i = 0; i < N; i++)
    tareaact.s[i] = (*d)->t.s[i];
  tareaact.fila = (*d)->t.fila;
  p = (*d);
  (*d) = (*d)->sig;
  free(p);
  return tareaact;
}

int valido(struct tarea tareaact, int col) {
  int i;

  for (i = 0; i < tareaact.fila; i++)
    if (tareaact.s[i]==col || tareaact.fila+col==tareaact.s[i]+i || col-tareaact.fila==tareaact.s[i]-i)
      return 0;
  return 1;
}

struct tarea ponerreina(struct tarea tareaact, int col) {
  int i;
  struct tarea nuevatarea;

  for (i = 0; i < tareaact.fila; i++)
    nuevatarea.s[i] = tareaact.s[i];
  nuevatarea.s[tareaact.fila] = col;
  for (i = tareaact.fila + 1; i < N; i++)
    nuevatarea.s[i] = -1;
  nuevatarea.fila = tareaact.fila + 1;
  return nuevatarea;
}

void insertar(struct nodo **d, struct tarea nuevatarea) {
  struct nodo *temp;
  int i;

  temp = (struct nodo *) malloc(sizeof(struct nodo));
  for (i = 0; i < N; i++)
    temp->t.s[i] = nuevatarea.s[i];
  temp->t.fila = nuevatarea.fila;
  temp->sig = (*d);
  (*d) = temp;
}

void reinas() {
  struct nodo *bolsa;
  struct tarea tareaact;
  int i;

  iniciar(&bolsa);
#ifdef DEBUG
  escribir(bolsa);
#endif
  while(!vacia(bolsa)) {
    tareaact = extraer(&bolsa);
#ifdef DEBUG
    escribir(bolsa);
#endif
    for (i = 0; i < N; i++) {    
      if (valido(tareaact, i)) {
        if (tareaact.fila < N-1) {
          insertar(&bolsa,ponerreina(tareaact, i));
#ifdef DEBUG
          escribir(bolsa);
#endif
        } else {
          printf("Solucion: ");
          escribirtarea(ponerreina(tareaact, i));
          printf("\n--------\n");
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {
  reinas();
}
