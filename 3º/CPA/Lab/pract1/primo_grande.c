#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <omp.h>

typedef unsigned long long Entero_grande;
#define ENTERO_MAS_GRANDE  ULLONG_MAX

int primo(Entero_grande n)
{
  int volatile p, hilo, nhilos, inc;
  Entero_grande i, s;

  p = (n % 2 != 0 || n == 2);

  if (p) {
    s = sqrt(n);

    #pragma omp parallel private(hilo, i)
    {
      #ifdef _OPENMP
        hilo = omp_get_thread_num();
        nhilos = omp_get_num_threads();
      #else
        hilo = 0; nhilos = 1;
      #endif

      inc = 2 * nhilos;

      for (i = 3 + 2 * hilo; p && i <= s; i += inc)
        if (n % i == 0) p = 0;
    }
  }

  return p;
}

int main()
{
  Entero_grande n;

  double t1, t2;

  #pragma omp parallel
  {
    if (omp_get_thread_num() == 0)
      printf("Número de hilos: %d\n", omp_get_num_threads());
  }

  t1 = omp_get_wtime();
  for (n = ENTERO_MAS_GRANDE; !primo(n); n -= 2) {
    /* NADA */
  }
  t2 = omp_get_wtime();

  printf("El mayor primo que cabe en %lu bytes es %llu. Tiempo = %.3f\n---\n",
         sizeof(Entero_grande), n, t2 - t1);
  

  return 0;
}
