/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 3, Código 3.11
* Programa "Hola" en OpenMP
*********************************************************************/

#include <stdio.h>
#include <omp.h>

int main ()  {
    int nthreads, tid;
    #pragma omp parallel private(tid)     // Expande un grupo de threads
                // Cada thread contiene sus propias copias de variables
    {
        tid = omp_get_thread_num(); // Obtiene el identificador del thread 
        nthreads = omp_get_num_threads(); // Obtiene el número de threads 
        printf("Hola desde el thread %d de %d threads\n", tid, nthreads);
    }  // Todos los threads se unen al thread maestro y finalizan
}
