/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 4, Códigos 4.1 y 4.2
* Suma de números en memoria compartida
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int THREADS;

//Código 4.2: Función que realiza la suma en memoria compartida

double suma(double *a, int t) {
    int i, iam, nprocs;
    double s, st;
    #pragma omp parallel shared(a) private(i, s, iam, nprocs)   
    {
        nprocs = omp_get_num_threads();
        iam = omp_get_thread_num();
        s = 0.;
        #pragma omp master
            THREADS = nprocs;
        #pragma omp for schedule(static)
// cada thread realiza una parte de la suma
        for (i = 0; i < t; i++)
            s += a[i];
        a[iam] = s;
    }   
    st = 0.;
// el maestro calcula la suma final
    for (i = 0; i < THREADS; i++)
        st += a[i];
    return st;
}

//Código 4.1: Programa principal y función auxiliar para el estudio
//experimental de la suma de números en memoria compartida
// función de generación de array de valores aleatorios entre 0 y 1
void initializealea(double *m, int t) {
    int i;
    for (i = 0; i < t; i++)
        m[i] = (double)rand()/RAND_MAX;
}

int main(int argc, char *argv[]) {
    long int t, iN, fN, incN;
    double start, fin, tiempo, Mflops;
    double *a, s;
// se realizan experimentos con distintos tamaños de datos
// desde iN hasta fN con incremento incN
    iN = atoi(argv[1]);
    fN = atoi(argv[2]);
    incN = atoi(argv[3]);
    for (t = iN; t <= fN; t += incN) {
        a = (double *) malloc(sizeof(double) * t);
        initializealea(a, t);
        start = omp_get_wtime();
        s = suma(a, t);
        fin = omp_get_wtime();
        tiempo = fin - start;
        if (tiempo == 0.) 
            printf("No hay suficiente precision\n");    
        else {
            Mflops = (t / tiempo) / 1000000.;
            printf("  threads %d, tamano %ld\n segundos: %.6lf, Mflops: %.6lf, Mflops por thread: %.6lf\n", THREADS, t, tiempo, Mflops, Mflops / THREADS);
            printf("   suma: %.4lf\n\n", s);
        }
        free(a);
    }
}
