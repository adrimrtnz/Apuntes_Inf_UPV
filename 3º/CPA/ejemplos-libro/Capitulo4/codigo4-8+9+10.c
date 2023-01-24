/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 4, Códigos 4.8, 4.9 y 4.10
* Multiplicación matriz-vector con paso de mensajes
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ENVIO_INICIAL_M 10
#define ENVIO_INICIAL_V 20
#define ENVIO_FINAL 30

void copiar(double *md, int nmd, double *mo, int nmo) {
    int i;

    for (i = 0; i < nmo; i++)
        md[i] = mo [i];
}

//Código 4.9: Envío inicial de datos en la multiplicación matriz-vector por
//paso de mensajes

void enviardatos(double *a, double *v, int t, double *al, int tl, int myid, int numprocs) {
    int i;
    int pos, tammin, tam;
    tammin = t / numprocs;
    if (myid == 0) {
        pos = tl;
// el proceso cero envía a los demás procesos
        for (i = 1; i < numprocs; i++) {
            tam = tammin;
            if ((t %  numprocs) > i)
                tam = tammin + 1;
// las filas correspondientes de la matriz
            MPI_Send(&a[pos * t], tam * t, MPI_DOUBLE, i, ENVIO_INICIAL_M, MPI_COMM_WORLD);
// y el vector completo
            MPI_Send(v, t, MPI_DOUBLE, i, ENVIO_INICIAL_V, MPI_COMM_WORLD);
            pos += tam;
        }
        copiar(a, tl * t, al, tl * t);
    } else {
        MPI_Recv(al, tl * t, MPI_DOUBLE, 0, ENVIO_INICIAL_M, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(v, t, MPI_DOUBLE, 0, ENVIO_INICIAL_V, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

//Código 4.10: Rutina de multiplicación matriz-vector con paso de mensajes

void mv(double *al,double *v,double *wl,double *w,int t,int tl, int myid,int numprocs) {
    int i, j, tammin, pos, tam;
    double s;
// cada proceso realiza la multiplicación de las filas de la matriz
// que ha recibido
    for (i = 0; i < tl; i++) {
        s = 0.;
        for (j = 0; j < t; j++)
          s = s + al[i * t + j] * v[j];
        wl[i] = s;
    }
    tammin = t / numprocs;
    if (myid == 0) {
        pos = tl;
// el proceso cero recibe los subvectores resultado
        for (i = 1; i < numprocs; i++) {
            tam = tammin;
            if (( t %  numprocs) > i)
// calculando el tamaño del vector a recibir
                tam = tammin + 1;
            MPI_Recv(&w[pos], tam, MPI_DOUBLE, i, ENVIO_FINAL, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            pos += tam;
       }
// copia en el vector resultado el trozo que él calculó
       copiar(wl, tl, w, tl);
    } else
        MPI_Send(wl, tl, MPI_DOUBLE, 0, ENVIO_FINAL, MPI_COMM_WORLD);
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
  int i, j;
  for (i = 0; i < fm; i++) {
    for(j = 0; j < cm;j++)
      printf("%.4lf ", m[i * ldm + j]);
    printf("\n");
  }
}

//Código 4.8: Función main de la multiplicación matriz-vector con paso de mensajes

int main(int argc, char *argv[]) {
    int t, iN, fN, incN, tl, myid, numprocs;
    double *a = NULL, *al = NULL, *v = NULL, *w = NULL, *wl = NULL;
    double  startwtime = 0.0,endwtime,totaltime;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    iN = atoi(argv[1]);
    fN = atoi(argv[2]);
    incN = atoi(argv[3]);

// se trabaja con distintos tamaños
    for (t = iN; t <= fN; t += incN) {
        tl = t / numprocs;
// algunos procesos trabajarán con una fila más que otros
        if ((t %  numprocs) > myid)  tl++;
        if (myid == 0) {
            a = (double *) malloc(sizeof(double) * t * t);
            w = (double *) malloc(sizeof(double) * t);
        }
        v = (double *) malloc(sizeof(double) * t);
        al = (double *) malloc(sizeof(double) * tl * t);
        wl = (double *) malloc(sizeof(double) * tl);
        if (myid == 0) {
            initialize(a, t * t);
            initialize(v, t);
        }
        MPI_Barrier(MPI_COMM_WORLD);
        startwtime = MPI_Wtime();
        enviardatos(a, v, t, al, tl, myid, numprocs);
        MPI_Barrier(MPI_COMM_WORLD);
        endwtime = MPI_Wtime();
        if (myid == 0)
            printf("procesadores %d, multiplicacion matriz-vector de tamano %d numeros\n    tiempo envio = %lf\n", numprocs, t, endwtime - startwtime);
        MPI_Barrier(MPI_COMM_WORLD);
        startwtime = MPI_Wtime();
        mv(al, v, wl, w, t, tl, myid, numprocs);
        MPI_Barrier(MPI_COMM_WORLD);
        endwtime = MPI_Wtime();
        totaltime = endwtime - startwtime;
        if (myid == 0)
            printf("    tiempo de multiplicacion= %lf, Mflops %lf, Mflops/nodo %lf\n", totaltime, ((2 * t * t) / totaltime) / 1000000, (((2 * t * t) / totaltime) / 1000000) / numprocs);
        if (myid == 0) {      
            free(a); 
            free(w);
        }
        free(al); 
        free(v); 
        free(wl);
    }
    MPI_Finalize();
}
