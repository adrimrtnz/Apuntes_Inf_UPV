/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 6, 
* Sección 6.7 Paralelismo síncrono: Códigos 6.22 y 6.23
* Algoritmo de Cannon para la multiplicación de matrices en una malla de procesos
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <mpi.h>

#define ENVIO_INI 1
#define ENVIO_FIN 2
#define ENVIO_INTA 3
#define ENVIO_INTB 4

void escribir(double *m, int f,int c,int ld){
  int i, j;

  for (i = 0; i < f; i++)
  {
    for (j = 0; j < c; j++)
    {  
      printf("%.4lf ",m[i*ld+j]);
    }
    printf("\n");
  }
}

void copiar(double *a,int fa,int ca,int lda,double *b,int fb,int cb,int ldb)
{
  int i,j;

  for(i=0;i<fa;i++)
    for(j=0;j<ca;j++)
      b[i*ldb+j]=a[i*lda+j];
}

void mms(double *a,int fa,int ca,int lda,double *b,int fb,int cb,int ldb,double *c,int fc,int cc,int ldc)
{
  int i, j, k;
  double s;

  for (i=0;i<fa;i++) 
    for(j=0;j<cb;j++)
    {
      s=c[i*ldc+j];
      for (k=0;k<ca;k++)
	s+=a[i*lda+k]*b[k*ldb+j];
      c[i*ldc+j]=s;
    }
}

// Código 6.23

void envioini(double *a, double *b, int n, double *ag, double *bg, int ng, int nodo, int np) {
    int i, j, k;
    double *m;
    if (nodo == 0)
// la matriz m se utiliza para copiar los datos a enviar 
// desde las matrices globales a zonas contiguas de memoria 
// (se podrían usar tipos derivados en MPI)
        m = (double *) malloc(sizeof(double) * n * n);
    if (nodo == 0) {
        copiar(ag, n, n, ng, a, n, n, n);
        copiar(bg, n, n, ng, b, n, n, n);
// se envía al resto de procesos en la primera fila de la malla
        for (i = 1; i < sqrt(np); i++) {
            copiar(&ag[n * i], n, n, ng, m, n, n, n);
            MPI_Send(m, n * n, MPI_DOUBLE, i, ENVIO_INI, MPI_COMM_WORLD);
        }
// y a los procesos en las filas restantes
        for (i = 1; i < sqrt(np); i++) {
            for (j = 0, k = i; j < sqrt(np); 
                               j++, k = ((++k) %  ((int) sqrt(np)))) {
                copiar(&ag[ng * i * n + k * n], n, n, ng, m, n, n, n);
                MPI_Send(m, n * n, MPI_DOUBLE, i * sqrt(np) + j, ENVIO_INI, MPI_COMM_WORLD);
            }
        }
// a la primera columna de la malla
        for (i = 1; i < sqrt(np); i++) {
            copiar(&bg[ng * n * i], n, n, ng, m, n, n, n);
            MPI_Send(m, n * n, MPI_DOUBLE, i * sqrt(np), ENVIO_INI, MPI_COMM_WORLD);
        }
// y al resto de columnas
        for (i = 1; i < sqrt(np); i++) 
            for(j = 0, k = i; j < sqrt(np); j++, k = ((++k) %  ((int) sqrt(np)))) {
                copiar(&bg[n * i + k * n * ng], n, n, ng, m, n, n, n);
                MPI_Send(m, n * n, MPI_DOUBLE, i + j * sqrt(np), ENVIO_INI, MPI_COMM_WORLD);
            }
        free(m);
    } else {
        MPI_Recv(a, n * n, MPI_DOUBLE, 0, ENVIO_INI, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b, n * n, MPI_DOUBLE, 0, ENVIO_INI, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

void enviofin(double *c,int N,double *cg,int Ng,int nodo,int np)
{
  int i,j,k;
  double *m;
  MPI_Status *estado=NULL;

  if(nodo==0)
    m=(double *) malloc(sizeof(double)*N*N);

  if(nodo==0)
  {    
    copiar(c,N,N,N,cg,N,N,Ng);
    for(i=1;i<sqrt(np);i++)
    {
      MPI_Recv(m,N*N,MPI_DOUBLE,i,ENVIO_FIN,MPI_COMM_WORLD,estado);
      copiar(m,N,N,N,&cg[i*N],N,N,Ng);
    }
    for(i=1;i<sqrt(np);i++)
    {
      for(j=0,k=i;j<sqrt(np);j++,k=((++k) % ((int) sqrt(np))))
      {
        MPI_Recv(m,N*N,MPI_DOUBLE,i*sqrt(np)+j,ENVIO_FIN,MPI_COMM_WORLD,estado);
        copiar(m,N,N,N,&cg[i*N*Ng+j*N],N,N,Ng);
      }
    }
    free(m);
  }
  else
    MPI_Send(c,N*N,MPI_DOUBLE,0,ENVIO_FIN,MPI_COMM_WORLD);
}

// Código 6.22

void mm(double *a, double *b, double *c, int n, double *ag,
        double *bg, double *cg, int ng, int nodo, int np) {
    int i, j, k, izq, der, arr, aba;
    double s;
// cada proceso obtiene sus procesos vecinos
    if ((nodo %  ((int) sqrt(np))) == 0)
        izq = nodo + sqrt(np) - 1;
    else
        izq = nodo - 1;
    if ((nodo %  ((int) sqrt(np))) == (sqrt(np) - 1))
        der = nodo - sqrt(np) + 1;
    else
        der = nodo + 1;
    if ((nodo / ((int) sqrt(np))) == 0)
        arr = nodo + (sqrt(np) - 1) * sqrt(np);
    else
        arr = nodo - sqrt(np);
    if ((nodo / ((int) sqrt(np))) == (sqrt(np) - 1))
        aba = nodo - (sqrt(np) - 1) * sqrt(np);
    else
        aba = nodo + sqrt(np);
// se envían los bloques de matrices según la distribución inicial
// a y b contendrán los bloques, de tamaño n
// y ag y bg las matrices globales, de tamaño ng, en el proceso cero
    envioini(a, b, n, ag, bg, ng, nodo, np);
// multiplicación secuencial
    mms(a, n, n, n, b, n, n, n, c, n, n, n);
// varias iteraciones
    for (i = 0; i < sqrt(np) - 1; i++) {
// donde cada proceso envía su bloque de a a la izquierda (cíclicamente)
// y su bloque de b hacia arriba (cíclicamente)
        MPI_Send(a, n * n, MPI_DOUBLE, izq, ENVIO_INTA, MPI_COMM_WORLD);
        MPI_Send(b, n * n, MPI_DOUBLE, arr, ENVIO_INTB, MPI_COMM_WORLD);
        MPI_Recv(a, n * n, MPI_DOUBLE, der, ENVIO_INTA, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b, n * n, MPI_DOUBLE, aba, ENVIO_INTB, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        mms(a, n, n, n, b, n, n, n, c, n, n, n);
    }
    enviofin(c, n, cg, ng, nodo, np);
}

/*
c
c initialize - random initialization for array
c
*/

void initializeA(double *m, int f,int c,int ld){
  int i, j;

  for (i = 0; i < f; i++)
  {
    for (j = 0; j < c; j++)
    {  
      m[i*ld+j] = (double)(i+j);
    }
  }
}

void initializeB(double *m, int f,int c,int ld){
  int i, j;

  for (i = 0; i < f; i++)
  {
    for (j = 0; j < c; j++)
    {  
      m[i*ld+j] = (double)(2*i+j);
    }
  }
}

void initializealea(double *m, int f,int c,int ld){
  int i, j;

  for (i = 0; i < f; i++)
  {
    for (j = 0; j < c; j++)
    {  
      m[i*ld+j] = (double)rand()/RAND_MAX;
    }
  }
}

void comparar(double *m1,int fm1,int cm1,int ldm1,double *m2,int fm2,int cm2,int ldm2)
{
  int i,j;

  for(i=0;i<fm1;i++)
    for(j=0;j<cm1;j++)
    {
      if(fabs(m1[i*ldm1+j]-m2[i*ldm2+j])>0.000001)
      {
        printf("Diferencia en %d,%d: %.8lf , %.8lf\n",i,j,m1[i*ldm1+j],m2[i*ldm2+j]);
        return;
      }
    }
}

int main(int argc,char *argv[]) {
  int nodo,np,i,j,N,Nl;
  int long_name;
  double ti,tf;
  double *a,*b,*c,*a0,*b0,*c0,*c0c;
  char    nombre_procesador[MPI_MAX_PROCESSOR_NAME];
  MPI_Status estado;
 
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&np);
  MPI_Comm_rank(MPI_COMM_WORLD,&nodo);
  MPI_Get_processor_name(nombre_procesador,&long_name);

  if(nodo==0)
  {
    N=atoi(argv[1]);
  }
  MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
  
  Nl=N/sqrt(np);
 
  if(nodo==0)
  {
    a0 = (double *) malloc(sizeof(double)*N*N);
    b0 = (double *) malloc(sizeof(double)*N*N);
    c0 = (double *) malloc(sizeof(double)*N*N);
    c0c = (double *) calloc(N*N,sizeof(double));
    initializealea(a0,N,N,N);
    initializealea(b0,N,N,N);
    mms(a0,N,N,N,b0,N,N,N,c0c,N,N,N);
  }
  a = (double *) malloc(sizeof(double)*Nl*Nl);
  b = (double *) malloc(sizeof(double)*Nl*Nl);
  c = (double *) calloc(Nl*Nl,sizeof(double));
  

  MPI_Barrier(MPI_COMM_WORLD);

  ti=MPI_Wtime();

  mm(a,b,c,Nl,a0,b0,c0,N,nodo,np);

  MPI_Barrier(MPI_COMM_WORLD);
  tf=MPI_Wtime();
  if(nodo==0)
  {
    printf("Proceso %d, %s, Tiempo %.6lf\n",nodo,nombre_procesador,tf-ti);
// Compara el resultado obtenido en secuencial y en paralelo
    comparar(c0c,N,N,N,c0,N,N,N);
  }
  
  free(a);
  free(b);
  free(c);
  if(nodo==0)
  { 
    free(a0);
    free(b0);
    free(c0);
    free(c0c);
  }
  MPI_Finalize();
}
