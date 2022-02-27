# Tema 2: Sincronización de tareas

## Objetivos

Revisión del concepto de programación concurrente:

* Identificar los problemas que conlleva la programación concurrente.
* Conocer los mecanismos de cooperación necesarios para implantar una aplicación concurrente (comunicación y sincronización).
* Identificar las partes del código que pueden ocasionar problemas (secciones críticas) y cómo protegerlas.

Conocer un lenguaje de programación que da soporte a la programación concurrente: Concurrencia en Java:

* Introducir los mecanismo básicos del lenguaje Java para soportar la programación concurrente.

## Concurrencia entre hilos: requisitos

La concurrencia implica **paralelismo** y **cooperación** de los hilos.

La **cooperación** requiere:

1. Comunicación (intercambio de información).
2. Sincronización (establecer determinado orden en casos concretos).

## Mecanismos de comunicación

**Memoria compartida:** los hilos comparten espacio de memoria (variables u objetos compartidos).

* Requiere mecanismos de sincronización para coordinar las tareas.

**Intercambio de mensajes:** emisor/receptor potencialmente en espacios de memoria disjuntos.

* Se verá en Sistemas Distribuidos. La tendencia actual es que las aplicaciones sean distribuidas.

El **objetivo** de estos mecanismos son:

* Garantizar orden de ejecución de sentencias.
* Respetar restricciones en la ejecución de código.

### Problemas que pueden aparecer

**Condiciones de Carrera:** modificación inconsistente de la memoria compartida.

* Pueden aparecer errores cuando múltiples hilos acceden a datos compartidos.
* Pueden aparecer errores de vistas inconsistentes de la memoria compartida.

> Con la **Sincronización** se previenen estos problemas.



```java
public class Counter {
    protected long count = 0;
    
    public void add(long x) {
        count += x;
    }
    
    public long getCount() {
        return count;
    }
}
// ...
Counter c = new Counter(); // Inicia a 0
```

En el ejemplo anterior imaginemos que tenemos un objeto c de tipo *Counter* y dos hilos A y B.

* c inicialmente vale 0.
* A ejecuta `c.add(3)`
* B ejecuta a la vez `c.add(2)`

El valor final de c debería ser 5. Sin embargo, esto depende del **intercambio exacto** (planificación) al ejecutar A y B.

* Se producen **interferencias** cuando dos operaciones, ejecutándose en diferentes hilos, pero actuando sobre los mismo datos, se **intercalan**.

## Tipos de Sincronización

**Exclusión mutua:**

* **Solamente un hilo** puede ejecutar la sección crítica en cada momento.
* Necesario para evitar interferencias entre hilos.
* Aplicarlo para variables/objetos compartidos.

**Sincronización condicional:**

* Un hilo debe suspenderse hasta que se cumpla determinada condición.
* La condición depende del valor de alguna variable compartida.
* Otros hilos, al modificar esas variables, conseguirán que se cumpla la condición, reactivando a los hilos suspendidos.

```java
// ...

// Protocolo de entrada

ejecucionSeccionCritica();

// Protocolo de salida

// ...
```

El **protocolo de entrada/salida** tiene que asegurar:

* **Exclusión mutua**.
* **Progreso:** todo servicio solicitado se completa en algún momento.
* **Espera limitada**.

Se dice que un código es **thread-safe** cuando puede ser ejecutado concurrentemente por distintos hilos de forma segura.

**Estrategias de solución según nivel**:

| Hardware                                                     | Sistema Operativo                                            | Lenguajes de Programación                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Inhabilitación de interrupciones. Sólo para codificar el núcleo del SO. | Llamadas al sistema para utilizar semáforos, mutex, eventos, condiciones. | Locks, condiciones, monitores, regiones críticas, objetos protegidos. |

Usando *locks* convertimos una sección crítica en una **acción atómica**:

* **Atomicidad**: únicamente un hilo puede ejecutar el código protegido en un momento dado.
* Garantiza actuación fiable de variables u objetos compartidos.
  * Libre de condiciones de carrera o corrupción de estado.
  * Sólo son visibles los estados consistentes.
  * Asegura que todo hilo accede siempre al valor más reciente de cada variable u objeto compartido.

![mutex](https://adit.io/imgs/concurrency/mutex.png)

Todo objeto posee un lock asociado **implicito**:

* Etiquetar con `synchronized` los métodos que forman parte de la sección crítica.
* Al entrar en un método etiquetado como `synchronized` se cierra el lock, y al salir se abre.
  * Al salir, se establece una relación **ocurre-antes** con otras invocaciones posteriores de métodos sincronizados del mismo objeto.
* Para un mismo objeto, todos sus métodos `synchronized` se ejecutan **en exclusión mutua entre sí**.

```java
public class Counter {
    protected long count = 0;
    
    public synchronized void add(long x) {
        count += x;
    }
    
    public synchronized long getCount() {
        return count;
    }
}
// ...
Counter c = new Counter(); // Inicia a 0
```

A parte de los **métodos sincronizados**, también se puede hacer uso de las **sentencias sincronizadas** (*Synchronized Statements*) indicando el objeto que proporciona el lock implícito.

* Permite utilizar más de un lock dentro de un mismo método.

```java
public class MsLunch {
    private long c1 = 0;
    private long c2 = 0;
    
    private Object lock1 = new Object();
    private Object lock2 = new Object();
    
    // De esta forma, los métodos inc1 e inc2 pueden
    // intercalarse, pero la actuación de c1 y c2 se
    // hacen en exclusión mutua.
    public void inc1() {
        synchronized(lock1) { 
            c1++; 
        }
    }
    
    public void inc2() {
        synchronized(lock2) { 
            c2++; 
        }
    }
}
```

