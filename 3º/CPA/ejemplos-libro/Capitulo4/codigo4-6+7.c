/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 4, Códigos 4.6 y 4.7
* Multiplicación matriz-vector en memoria compartida
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int THREADS;

//Código 4.7: Multiplicación matriz-vector en memoria compartida

void mv(double *m, int fm, int cm, int ldm, double *v, int fv, 
        double *w, int fw) {
    int i, j, iam, nprocs;
    double s;
    #pragma omp parallel private(iam, nprocs)   
    {
        nprocs = omp_get_num_threads();
        iam = omp_get_thread_num();
// el maestro obtiene el número de threads, que se usará en el programa 
// principal
        #pragma omp master
            THREADS = nprocs;
// cada thread trabaja con varias filas de la matriz
        #pragma omp for private(i, s, j) schedule(static)
        for (i = 0; i < fm; i++) {
            s = 0.;
            for(j = 0; j < cm; j++)
              s += m[i * ldm + j] * v[j];
            w[i] = s;
        }
    }
}

void initialize(double *m, int t) {
  int i;
  for (i = 0; i < t; i++)
    m[i] = (double)(i);
}

void initializealea(double *m, int t) {
  int i;
  for (i = 0; i < t; i++)
    m[i] = (double)rand()/RAND_MAX;
}

void escribir(double *m, int fm, int cm, int ldm) {
  int i,j;
  for (i = 0; i < fm; i++) {
    for (j = 0; j < cm; j++)
      printf("%.4lf ", m[i * ldm + j]);
    printf("\n");
  }
}

//Código 4.6: Función main del programa de multiplicación matriz-vector en
//memoria compartida

int main(int argc, char *argv[]) {
    int t, iN, fN, incN;
    double start, end, tiempo, Mflops;
    double *a, *v, *w;
    iN = atoi(argv[1]);
    fN = atoi(argv[2]);
    incN = atoi(argv[3]);
// se realizan multiplicaciones con matrices y vectores de distintos 
// tamaños
    for (t = iN; t <= fN; t += incN) {
        a = (double *) malloc(sizeof(double) * t * t);
        v = (double *) malloc(sizeof(double) * t);
        w = (double *) malloc(sizeof(double) * t);
        initializealea(a, t * t);
        initializealea(v, t);
        start = omp_get_wtime();
        mv(a, t, t, t, v, t, w, t);
        end = omp_get_wtime();
        tiempo = end - start;
        if (tiempo == 0.) 
            printf("No hay suficiente precision\n");
        else {
            Mflops = ((2. * t * t) / tiempo)/ 1000000. ;
            printf("  threads %d, tamano %d\n    segundos: %.6lf, Mflops: %.6lf, Mflops por thread: %.6lf\n", THREADS, t, tiempo, Mflops, Mflops / THREADS);
        }
        free(a);
        free(v);
        free(w);
    }
}
