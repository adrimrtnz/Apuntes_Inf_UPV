/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.10 Trabajadores replicados: Código 6.29
* Solución del problema de las reinas en OpenMP,
* con generación de un conjunto de tareas inicial que se asigna a los
* trabajadores sin que éstos generen nuevas tareas
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define N 8

int valido(int * tarea, int col, int fil) {
  int i;

  for (i = 0; i < fil; i++)
    if (tarea[i]==col || fil+col==tarea[i]+i || col-fil==tarea[i]-i)
      return 0;
  return 1;
}

void insertar(int *tareas, int nivel, int *tarea, int *pos) {
  int i;

  for (i = 0; i < nivel; i++)
    tareas[ i + (*pos)] = tarea[i];
  (*pos) = (*pos) + nivel;
}

void escribir(int *m, int tam, int nivel) {
  int i, j;

  for (i = 0; i < tam; i++) {
    for (j = 0; j < nivel; j++)
      printf("%d, ",m[i * nivel + j]);
    printf(" + ");
  }
  printf("*\n");
}

void ponertareas(int *tareas, int nivel, int n, int *tarea, int lt, int *pos) {
  int i;

  if (lt == nivel-1) {
    for (i = 0; i < n; i++)
      if (valido(tarea, i, lt)) {
        tarea[lt] = i;
        insertar(tareas, nivel, tarea, pos);
      }
  } else
      for (i = 0; i < n; i++)
        if (valido(tarea, i, lt)) {
          tarea[lt]=i;
          ponertareas(tareas,nivel,n,tarea,lt+1,pos);
        }
}

void escribirsolucion(int *s, int n) {
  int i;

  for (i = 0; i < n; i++)
    printf("%d ,", s[i]);
  printf("+\n");
}

int iniciar(int *tareas, int nivel, int n) {
  int i, pos = 0, *tarea, lt = 0;

  tarea = (int *) malloc(sizeof(int) * nivel);
  
  ponertareas(tareas, nivel, n, tarea, lt, &pos);
  return pos / nivel;
  free(tarea);
}

void back(int *s, int n, int nivel) {
    int i;
    if (nivel == n - 1) {
        for (i = 0; i < n; i++)
            if (valido(s, i, nivel)) {
                s[nivel] = i;
                escribirsolucion(s, n);
            }
    } else
        for (i = 0; i < n; i++)
            if (valido(s, i, nivel)) {
                s[nivel] = i;
                back(s, n, nivel + 1);
            }
}

void backtracking(int *tarea, int nivel,int n) {
    int *s, i;
    s = (int *) malloc(sizeof(int) * n);
// se sitúa una reina en cada columna en la fila siguiente
    for (i = 0; i < nivel; i++)
        s[i] = tarea[i];
// y se realiza backtracking a partir de cada configuración
    back(s, n, nivel);
    free(s);
}

// nivel indica hasta qué nivel genera tareas el maestro
void reinas(int THREADS, int nivel,int n) {
    int *tareas, maxtareas = n, tam = 0;
    int i;
    for (i = 1; i < nivel; i++)
        maxtareas *= n - i;
// asigna espacio para el máximo de tareas que puede generar
    tareas = (int *) malloc(sizeof(int) * maxtareas * nivel);
    omp_set_num_threads(THREADS);
// el maestro genera las tareas hasta ese nivel
    tam = iniciar(tareas, nivel, n);
// se hace un reparto cíclico para intentar equilibrar la carga
    #pragma omp parallel for private(i) schedule(static, 1)
    for (i = 0; i < tam; i++)
        backtracking(&tareas[i * nivel], nivel, n);
    free(tareas);
}

int main(int argc,char *argv[]) {

//El argumento 1 es el número de threads a usar, y el dos el nivel hasta el que se
//genera inicialmente para formar la bosa de tareas

  reinas(atoi(argv[1]), atoi(argv[2]), N);
}
