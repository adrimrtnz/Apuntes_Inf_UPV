/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 3, Código 3.13
* La directiva for
*********************************************************************/

#include <stdio.h>
#include <omp.h>
#define CHUNKSIZE 2
#define N    10

int main () {
    int i, chunk;
    int nthreads, tid;
    int a[N], b[N], c[N];
    // Algunas inicializaciones
    for (i = 0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    chunk = CHUNKSIZE;
    // Las variables a, b, c, chunk son de tipo compartido
    // Las variables i, tid  son privadas a cada thread 
    #pragma omp parallel shared(a, b, c, chunk) private(i, tid)
    {
        // Se realiza una asignación estática de iteraciones
        // en la que el tamaño del bloque se fija a chunk
        #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++) {
            tid = omp_get_thread_num();
            nthreads = omp_get_num_threads();
            c[i] = a[i] + b[i];
            printf("El thread %d, de %d threads, calcula la iteracion i =%d\n", tid, nthreads, i); 
        }
    }  // Fin de la región paralela
}
