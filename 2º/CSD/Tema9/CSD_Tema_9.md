# Unidad 9: Algoritmos distribuidos

## Objetivos de la Unidad Didáctica

* Conocer las **características** de los algoritmos distribuidos y ejemplos relevantes de los mismos.
* Comprender las dificultades de la **sincronización temporal**, al no existir un reloj único que todos los nodos puedan consultar.
* Comprender la **gran variedad** de problemas algorítmicos que surgen en sistemas distribuidos, identificando algunos de los más relevantes: consenso, elección de líder, exclusión mutua.
* Conocer algunos de los **algoritmos** a nivel básico, estudiando su funcionamiento, sus características, su complejidad y coste y el hecho de si toleran fallos o no.
* Identificar los fallos en los nodos como la mayor fuente de **complejidad** en el diseño de algoritmos distribuidos.

## 1. Sincronización de relojes físicos

En los sistemas distribuidos, la sincronización es más compleja que en los sistemas centralizados. Por ejemplo, el acceso en exclusión mutua a un recurso compartido es más complejo cuando tenemos diferentes procesos en nodos distintos que desean acceder a un mismo recurso.

Como cada nodo tiene su propio reloj local, y además los chips de reloj no son absolutamente exactos, requerimos de algoritmos que nos permitan sincronizar los relojes físicos. 

### Algoritmo de Cristian

#### Para qué sirve

Sirve para sincronizar el reloj local **Cc** de un ordenador **cliente** con el reloj local **Cs** de un ordenador **servidor**.

Consideraciones:

* El ordenador servidor dispone de un reloj muy preciso, posiblemente sincronizado con otros más precisos todavía.
* Los relojes no deben retroceder (hay  aplicaciones a las que este retroceso les puede ocasionar algún tipo de problema).
* La sincronización requiere intercambio de mensajes, pero el tránsito de estos consume tiempo.

#### Descripción

Este algoritmo funciona de la siguiente forma:

1. El cliente pide el valor del reloj al servidor en **T0** (según **Cc**).
2. El servidor contesta con el valor de su reloj **Cs**.
3. La respuesta llega al cliente en **T1** (según **Cc**).
4. $C=Cs+\frac{(T_1-T_0)}{2}$
5. Si $C > Cc, Cc = C$
6. Si $C < Cc$ se detiene **Cc** las siguientes $Cc - C$ unidades de tiempo.

#### Análisis

* En este algoritmo se asume que el tiempo de envió de ambos mensajes es prácticamente igual.
* Si uno de los dos mensajes tarda más en ser transmitido, el ajuste no es correcto.
  * Generalmente la duración de ambos mensajes es igual.
* En todo caso, la sincronización perfecta es imposible (con este algoritmo o con cualquier otro).
* El correcto funcionamiento de una aplicación distribuida podrá depender de los valores de los relojes locales, solo si se tolera el margen de error inherente al algoritmo de sincronización utilizado.

### Algoritmo de Berkeley

Otra solución a la sincronización de relojes físicos la proporciona el **algoritmo de Berkeley**, cuyo objetivo consiste en sincronizar los relojes de todos los nodos entre sí.

#### 1. Introducción

Grupo de nodos formado por:

* Un servidor, denominado **S**.
* N clientes, denominados **Ci**.

Cada nodo dispone de su propio reloj local.

El **objetivo** es sincronizar los relojes locales de todos los nodos entre sí.

De forma periódica, a iniciativa del servidor, todos los nodos sincronizan sus relojes, empleando un protocolo de intercambio de mensajes.

#### 2. Descripción del algoritmo

1. El algoritmo comienza a iniciativa del servidor. Lee su reloj local y lo transmite a los ordenadores clientes. A este instante de tiempo lo denominamos $T_0$.
2. Transcurrido un tiempo, el mensaje llega a los clientes.
3. Cada cliente calcula la diferencia **Di** entre su reloj local y el que le ha sido notificado por el servidor en el mensaje.
4. Cada cliente notifica dicha diferencia al ordenador servidor.
5. La respuesta llega al servidor $T1_i$.
6. Se ajusto la diferencia de cada uno de los ordenadores cliente para eliminar el efecto del tiempo consumido por el envío y la recepción de mensajes $D_i'=D_i-\frac{(T1_i-T_0)}{2}$ .
7. Se calcula la diferencia media, incluyendo al servidor $D=\frac{\Sigma D_i}{(N+1)}$ .
8. El servidor ajusta su propio reloj incrementándolo **D**.
9. Se notifica el ajuste a cada uno de los ordenadores cliente $A_i = D-D_i$ .
10. Los mensajes llegan a los clientes.
11. Cada cliente ajusta su reloj local en función del ajuste notificado por parte del servidor $A_i$.

#### 3. Consideraciones adicionales

* No persigue sincronizar todos los relojes con el instante "real", sino llegar a un acuerdo entre los nodos.
* Si alguna diferencia $D_i$ es muy distinta a las demás, no se tiene en cuenta.
* Si el servidor falla, se inicia un algoritmo de elección de líder para escoger otro servidor.
* La sincronización exacta es imposible debido a la variabilidad del tiempo en la transmisión de los mensajes.

## Lección 2: Relojes lógicos y Relojes vectoriales

En muchas aplicaciones distribuidas no es necesario que los nodos tengan sus relojes físicos sincronizados, sino que solamente requiere conocer el orden en el que ocurren los eventos. En 1978, [Leslie Lamport]([Leslie Lamport - Wikipedia, la enciclopedia libre](https://es.wikipedia.org/wiki/Leslie_Lamport)) definió el concepto de [**relojes lógicos**]([Tiempos lógicos de Lamport - Wikipedia, la enciclopedia libre](https://es.wikipedia.org/wiki/Tiempos_lógicos_de_Lamport)), que permiten indicar el orden en que suceden ciertos eventos.

## Lección 3: Estado Global

## Lección 4: Exclusión mutua

## Lección 5: Elección de líder

## Lección 6: Consenso

**Definición del Problema del Consenso:** No es necesario que los nodos conozcan quién (Nodo "j") ha propuesto el valor propuesto y consensuado, pero es necesario que tal nodo exista.

* El acuerdo debe haber surgido adoptando la estimación de algún nodo.

* **No es consenso** decidir un valor "derivado" o generado a partir de las estimaciones.
  
  * En esos casos se trata de problemas diferentes a consenso.

Toda solución correcta del consenso debe cumplir las siguientes condiciones:

* Viveza: 
  
  * Terminación: todo nodo correcto tarde o temprano decide algún valor.

* Seguridad:
  
  * Integridad uniforme: todo nodo decide como máximo una vez.
  
  * Acuerdo: ningún par de nodos correctos decide de manera diferente.
  
  * Validez uniforme: si un nodo decide **v**, entonces **v** fue propuesto por algún nodo.



## Lección 7: Algoritmos de consenso en presencia de fallos
