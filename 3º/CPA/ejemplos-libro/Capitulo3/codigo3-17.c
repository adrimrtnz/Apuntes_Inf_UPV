/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 3, Código 3.17
* Utilización del constructor critical en OpenMP
*********************************************************************/

#include <stdio.h>
#include <omp.h>

int main() {
    int x, tid;
    x = 0;

    #pragma omp parallel shared(x) private(tid) 
    {
        tid = omp_get_thread_num();
        // Cada thread realiza alguna tarea
        #pragma omp critical
	{
            x = x + 1;
	    printf("Valor de x en thread %d: %d\n", tid, x);
        }
    }   // Fin de la región paralela
}
