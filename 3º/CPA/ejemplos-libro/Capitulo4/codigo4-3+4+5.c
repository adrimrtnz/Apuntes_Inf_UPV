/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 4, Códigos 4.3, 4.4 y 4.5
* Suma de números con paso de mensajes
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>
#define ENVIO_INICIAL 1
#define ENVIO_FINAL 2

void initializealea(double *m, int t) {
  int i;
  for (i = 0; i < t; i++)
    m[i] = (double)rand()/RAND_MAX;
}

void copiar(double *ao, int to, double *ad, int td) {
  int i;
  for (i = 0; i < to; i++)
    ad[i] = ao[i];
}

//Código 4.4: Función de envío de datos

void enviardatos(double *a, int t, double *al, int tl, 
                 int myid, int numprocs) {
    int i;
    int pos, tammin, tam;
    tammin = t / numprocs;
    if (myid == 0) {
        pos = tl;
// el proceso cero envía un trozo del array a cada uno de los restantes 
// procesos
        for (i = 1; i < numprocs; i++) {
            tam = tammin;
// calcula la cantidad de datos a enviar
            if ((t % numprocs) > i)
                tam = tammin + 1;
            MPI_Send(&a[pos], tam, MPI_DOUBLE, i, ENVIO_INICIAL, MPI_COMM_WORLD);
// y actualiza la posición de trabajo dentro del array
            pos += tam;
        }
        copiar(a, tl, al, tl);
    } else
        MPI_Recv(al, tl, MPI_DOUBLE, 0, ENVIO_INICIAL, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

//Código 4.5: Función que realiza la suma con paso de mensajes

double sumar(double *a, int t, int myid, int numprocs) {
    int i;
    double s = 0., sl;
// cada proceso suma los datos que ha recibido
    for (i = 0; i < t; i++)
        s += a[i];
    if (myid == 0) {
// y el proceso cero recibe las sumas parciales y calcula la suma total
        for (i = 1; i < numprocs; i++) {
          MPI_Recv(&sl, 1, MPI_DOUBLE, i, ENVIO_FINAL, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          s += sl;
        }  
    } else 
        MPI_Send(&s, 1, MPI_DOUBLE, 0, ENVIO_FINAL, MPI_COMM_WORLD);
    return s;
}

//Código 4.3: Progrma principal de la suma de datos con paso de mensajes

int main(int argc, char *argv[]) {
    int t, iN, fN, incN, tl;
    double *a, *al, s;
    int myid, numprocs;
    double startwtime = 0.0, endwtime, totaltime;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Get_processor_name(processor_name, &namelen);

    iN = atoi(argv[1]);
    fN = atoi(argv[2]);
    incN = atoi(argv[3]);
// se realizan experimentos con varios tamaños
    for (t = iN; t <= fN; t += incN) {
        tl = t / numprocs;
// algunos procesos tendrán un dato más que los otros
        if ((t % numprocs) > myid)
            tl++;
        if (myid == 0) {
            a = (double *) malloc(sizeof(double) * t);
// los datos están incicialmente en el proceso cero
            initializealea(a, t);
        }
        al = (double *) malloc(sizeof(double) * tl);
        MPI_Barrier(MPI_COMM_WORLD);
        startwtime = MPI_Wtime();
        enviardatos(a, t, al, tl, myid, numprocs);
        MPI_Barrier(MPI_COMM_WORLD);
        endwtime = MPI_Wtime();
        if (myid == 0)
            printf("procesadores %d, suma de %d numeros\n tiempo envio = %lf\n", numprocs, t, endwtime - startwtime);
        MPI_Barrier(MPI_COMM_WORLD);
        startwtime = MPI_Wtime();
        s = sumar(al, tl, myid, numprocs);
        MPI_Barrier(MPI_COMM_WORLD);
        endwtime = MPI_Wtime();
        totaltime = endwtime - startwtime;
        if (myid == 0)
            printf("    suma: %lf,    tiempo de suma = %lf, Mflops %lf, Mflops/nodo %lf\n", s, totaltime, (t / totaltime) / 1000000, ((t / totaltime) / 1000000) / numprocs);
        if (myid == 0)
            free(a);
        free(al);
    }
    MPI_Finalize();
    return 0;
}
