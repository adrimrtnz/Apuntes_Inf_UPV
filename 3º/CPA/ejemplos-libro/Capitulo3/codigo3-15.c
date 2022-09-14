/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 3, Código 3.15
* La directiva parallel for
*********************************************************************/

#include <stdio.h>
#include <omp.h>
#define N   10 
#define M   10

int main () {
    int i, j;
    int nthreads, tid;
    int n, m, sum;
    int a[M], c[N], b[M][N];
    // Inicializa b, c, m, n
    m = M;
    n = N;
    for (i = 0; i < n; i++)
      c[i] = i;
    for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
        b[i][j] = i + j;
    // Las variables a, b, c, m, n, nthreads son de tipo compartido
    // Las variables i, j, sum, tid son de tipo privado
    #pragma omp parallel for default(none) \
    private(tid, i, j, sum) shared(m, n, a, b, c, nthreads)
    for (i = 0; i < m; i++) {
        tid = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        sum = 0;
        for (j = 0; j < n; j++)
            sum += b[i][j] * c[j];
         a[i] = sum;
         printf("El thread %d, de %d threads, calcula la iteracion i = %d\n", tid, nthreads, i); 
    }
}
