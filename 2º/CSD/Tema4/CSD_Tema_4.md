# Tema 4: Interbloqueos

Un **interbloqueo** se produce cuando un conjunto de hilos no pueden evolucionar porque <u>se esperan mutuamente</u>.

## Problema de los 5 Filósofos

<img title="Problema de los 5 Filósofos" src="https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png" alt="" width="403" data-align="center">

> El **problema de la cena de los filósofos** es un problema clásico de las ciencias de la computación propuesto por Edsger Dijkstra en 1965 para representar el problema de la sincronización de procesos en un sistema operativo. El problema original está basado en pensadores chinos, quienes comían con dos palillos. [*(Wikipedia)*]([Problema de la cena de los filósofos - Wikipedia, la enciclopedia libre](https://es.wikipedia.org/wiki/Problema_de_la_cena_de_los_fil%C3%B3sofos))

```java
while(true) {
    pensar();
    cogerTenedor(derecho);
    cogerTenedor(izquierdo);
    comer();
    dejarTenedor(izquierdo);
    dejarTenedor(derecho);
}
```

* Cada par de filósofos vecinos **comparten** un tenedor, que utilizan en **exclusión mutua**.

* **Sincronización condicional:** Si no se dispone de ambos tenedores, no se puede empezar a comer.

* **Se pueden producir interbloqueos:** Si llegan a la vez a la mesa y todos cogen el tenedor derecho antes de que alguien pida su tenedor izquierdo.

## Condiciones de Coffman

**Cuatro condiciones** necesarias para que se de una situación de interbloqueo:

* **Exclusión mutua:** mientras una instancia de un proceso esté accediendo a un recurso, otras instancias no podrán obtener el mismo recurso.

* **Retención y espera:** como los recursos se solicitan a medida que se necesitan, un proceso podrá tener algún recurso asignado y solicitar otro que en ese momento no esté disponible, obligándolo a suspenderse.

* **No expulsión:** Un recurso que ya esté asignado solo podrá liberarlo su dueño. El gestor de recursos no podrá expropiarlo.

* **Espera circular:** En el grupo de procesos interbloquados, cada uno está esperando un recurso asignado a otro.

| Características                                                                                             |
|:----------------------------------------------------------------------------------------------------------- |
| Si todas las condiciones se cumplen simultaneamente en un sistema $\rightarrow$ **riesgo de interbloqueo**. |
| Si hay un interbloqueo $\rightarrow$ seguro que **todas se cumplen**.                                       |
| Las dos condiciones anteriores son **necesarias** pero **no suficientes**.                                  |

Para anlizar si en un sistema se está dando una situación de interbloqueo se usa un **grafo de asignación de recursos (GAR)**.

<img title="" src="https://www.gatevidyalay.com/wp-content/uploads/2018/10/Resource-Allocation-Graph-Problem-03.png" alt="Resource Allocation Graph" data-align="center">

En dicho grafo los procesos se representan con círculos (*P0, P1,etc*) y los recursos con rectángulos, que tendrán tantos puntos internos como instancias tengan.

Este grafo tiene dos tipos de aristas dirigidas (arcos):

* **Arcos de petición:** que salen de un proceso en dirección a un recurso. Representa la solicitud de un recurso por parte de un proceso e indica que tal petición no ha podido ser satisfecha de manera inmediata, por no haber suficientes instancias libres, quedando el proceso bloqueado al realizar tal petición.

* **Arcos de asignación**: que salen de un recurso y van hacia un proceso. Indica que una instancia ha podido ser asignada a un proceso y que este todavía la utiliza.

Analizando el **GAR** se puede determinar si hay o no riesgo de interbloqueo, para ello miramos si hay ciclos dirigidos: 

* Si los hay existe **riesgo** de interbloqueo. 
  
  * Si todos los recursos del ciclo son de 1 instancia $\rightarrow$ **interbloqueo**.
  
  * Si existe una **secuencia segura** (un orden en el que vayan terminando todos los hilos o procesos) $\rightarrow$ **no hay interbloqueo**.

## Soluciones al interbloqueo

Existen diferentes estrategias, que de **mejor a peor** son:

1. **Prevención**: diseñar un sistema que **rompa** alguna Condición de Coffman

2. **Evitación**: Monitorizar cada una de las peticiones de los procesos y se analiza con un **GAR**. Si una solicitud crea un ciclo (*riesgo de interbloqueo*), se deniega esa solicitud.

3. **Detección y recuperación**: El sistema monitoriza periódicamente su estado, y utiliza los **GAR** para detectar si ya hay un interbloqueo:
   
   * Detección: se monitoriza periódicamente el sistema.
   
   * Recuperación: si hay interbloqueo, se aborta alguna actividad involucrada.

4. **Ignorar el problema**: No resulve nada. Es el propio usuario el que debe detectar y solucionar el problema del interbloqueo. Pese a ser la peor, es utilizada en muchos sistemas operativos como Unix y Windows.

#### ¿Cómo llevar a cabo la **prevención**?

* La condición de **Exclusión Mutua** viene fijada por la propia naturaleza del recurso. Normalmente los recursos suelen usarse en exclusión mutua, por tanto esta condición es dificil de romper.

* La condición de **Retención y Espera** es una consecuencia de la forma habitual de la que los procesos usan los recursos. Para romperla se puede:
  
  * Pedir inicialmente TODO lo que podemos necesitar.
  
  * Solicitar recursos de modo no bloqueante.
  
  * **Estas soluciones disminuyen** la **concurrencia**, la **utilización de recursos** y hacen **posible la inanición** de hilos.

* La condición de **No expulsión** se puede romper permitiendo que un hilo expropie recursos de otro hilo. Esto implicará que el hilo expropiado debe volver a solicitar sus recursos. Para que esto pueda funcionar se debe ordenar de alguna forma los procesos (como dándoles prioridad), si no podríamos llegar al **Livelock** donde los procesos se expropian los procesos mutuamente, no quedando bloquados pero tampoco pudiendo avanzar.

* La condición de **Espera circular** se puede romper estableciendo un **orden** total entre los recursos, obligando a solicitar los recursos en orden. Es la **condición más fácil de romper**.
