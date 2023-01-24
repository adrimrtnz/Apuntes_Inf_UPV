/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.4 Esquemas en árbol y grafo: Código 6.13
* Obtención de clases de equivalencia en OpenMP
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void escribir(int *m, int t) {
  int i;

  for (i = 0; i < t; i++) {
    printf("%d ", m[i]);
  }
  printf("\n");
}

void copiar(int *ao, int *ad, int t) {
  int i;

  for(i = 0; i < t; i++)
    ad[i] = ao[i];
}

void equivalencia(int *a, int n) {
    int i, *repr, cont;
    repr = (int *) malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        repr[i] = a[i];
    cont = 1;
// mientras haya cambios
    while (cont) {
        cont = 0;
// se crean threads y se reparte la actualización de los representantes
        #pragma omp parallel for private(i) 
        for (i = 0; i < n; i++)
            if (repr[i] != repr[a[i]]) {      
                cont = 1;
                repr[i] = repr[a[i]];
            }
    }
    copiar(repr, a, n);
    free(repr);
}

void initializealea(int *m, int t){
  int i,nc,pos;

  nc= ((1.*rand())/RAND_MAX)*t/2+1;
 
  i=0;
  while(i<nc)
  {
    pos= ((1.*rand())/RAND_MAX)*t;
    if(m[pos]==-1)
    {
      m[pos]=pos;
      i++;
    }
  }
  for (i = 0; i < t; i++)
    if(m[i]==-1)
      m[i] = ((1.*rand())/RAND_MAX)*t;
}

/*
c
c     mseconds - returns elapsed microseconds since Jan 1st, 1970.
c
*/
double mseconds() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec * 1000000. + t.tv_usec;
}

int main(int argc, char *argv[]) {
  long int t, i;
  double start, fin, tiempo, Mflops;
  int *a;

//Ejecución: ejecutable tamañoconjunto

  t = atoi(argv[1]);
  a = (int *) malloc(t * sizeof(double));
  for (i = 0; i < t; i++)
    a[i] = -1;

  initializealea(a, t);
#ifdef DEBUG    
  escribir(a, t);
#endif
  start = mseconds();

  equivalencia(a, t);

  fin = mseconds();
#ifdef DEBUG
  escribir(a, t);
#endif
  free(a);
}

