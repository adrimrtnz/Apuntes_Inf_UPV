# Tema 5: Otras herramientas de sincronización

## Inconvenientes de las primitivas básicas de Java

**Limitaciones** de las primitivas basicas de Java relacionadas con la **exclusión mutua**:

1. No se puede establecer un plazo máximo de espera a la hora de "solicitar" la entrada al monitor: 
   * Si el monitor está ocupado, el hilo se queda esperando y no se le puede interrumpir voluntariamente.
2. No se puede preguntar por el estado del monitor antes de solicitar el acceso al mismo.
   * En ocasiones interesa consultar si el lock (o monitor) está libre u ocupado sin necesidad de bloquarse (`tryLock()`).
3. Las herramientas que garantizan exclusión mutua está orientadas a bloques.
4. No podemos extender su semántica.
   * En problema *lectores-escritores*, no podemos definir exclusión mutua solamente entre hilos escritores-escritores y escritores-lectores.

Limitaciones relacionadas con la **sincronización condicional**:

1. Sólo podrá existir una única condición en cada monitor.
2. Se utiliza la variante de Lampson y Redell.
   * El programador está obligado a utilizar una estructura del tipo: `while(expresión lógica) wait();` para consultar el estado del monituro y suspenderse.

## Biblioteca java.util.concurrent

J2SE 5.0 introduce el paquete `java.util.concurrent`:

* Ofrece construcciones de alto nivel.
* Garantizan: +Productividad, +Prestaciones, +Fiabilidad.

Esta biblioteca incluye varios elementos útiles:

* **Locks**.
  * Diferentes clases e interfaces para **múltiples tipos de locks**.
  * Características:
    * Indicar gestión equitativa (***fair***) de cola de espera.
    * Distintos tipos de locks, con semática diferente.
    * Método `tryLock()`  que no suspende al hilo invocador si lock ya cerrado por otro hilo. Se rompe así la condición de retención y espera de Coffman
* **Variables condición**.
* Colecciones concurrentes.
* Variables atómicas.
* Entorno para la ejecución de hilos.
* Sincronización: Semáforos y Barreras.
* Temporización precisa.

### Locks: ReentrantLocks

El **ReentrantLock** se puede reutilizar en la misma sección sin problemas de bloqueo.

Resuelve las limitaciones de las sentencias `synchronized`:

* Permite especificar un **plazo máximo de espera** para obetener el lock $\rightarrow$ `tryLock()` con timeout.
* Definir distintas variables condición $\rightarrow$ método `newCondition()`.
* Cerra y abrir los locks en diferentes métodos $\rightarrow$ `lock()`, `unlock()`.
* Interrumpir esperas $\rightarrow$ `Thread.interrupt()`.

Aunque tiene algunos inconvenientes:

* El *lock* ya no se abre por defecto al terminar un bloque de código. El programador debe abrirlo explícitamente.
* Asegurarse de **abrir el lock** correspondiente al librera un recurso que se use en exclusión mutua.
* Controlar las excepciones que se puedan generar dentro de una sección crítica protegida por un *ReentrantLock*.
  * Asegurarse de **abrir el lock** en el código de la excepción.

```java
// Recomendación: seguir esta estructura de
// los protocolos de entrada y salida.
Lock x = new ReentrantLock();

x.lock();            // Protocolo de entrada

try {
    // Sección crítica
    // ...
} finally {
    x.unlock();      // Asegurarse que siempre se libere el recurso
}
```

### Variables condición

La interfaz `Condition`permite declarar cualquier número de variables condición en un lock:

* Ofrece un código más legible y eficiente.

El objeto lock actúa como una factoría para variables condición asociadas al mismo:

* Sólo podemos definir variables **condición** dentro de un mismo lock.

Método `newCondition()` de la clase `ReentrantLock`:

* Permite generar todas las colas de espera (condiciones) que resulten necesarias.
* Devuelve un objeto que implanta la interfaz `Condition`.

Métodos de la interfaz `Condition`:

* `await()`: suspende a un hilo en la condición.
* `signal()`: notifica a **uno** de los hilos que estuviera esperándolo.
* `signalAll()`: notifica a **todos** los hilos suspendidos en la condición.

Estos métodos actuan sobre el lock asociado a la **condición**,  mientras que los métodos `wait()`, `notify()`, `notifyAll()` actuan sobre el lock asociado al **objeto** correspondiente.

```java
import java.util.concurrent.*;
import java.util.concurrent.locks.*;

class BufferOk implements Buffer {
    private int elemns, cabeza, cola, N;
    private int[] datos;

    ReentrantLock lock;
    Condition noLLeno, noVacio;

    public BufferOk(int N) {
        datos = new int[N];
        this.N = N;
        cabeza = cola = elems = 0;

        lock = new ReentrantLock();      // en semáforos esto es el MUTEX
        noLLeno = lock.newCondition();
        noVacio = lock.newCondition();
    }

    // Método productor
    public void put(int x) {
        try {
            lock.lock();
            while(elems == N) {
                System.out.println("productor esperando...");
                try { noLleno.await(); }
                catch(InterruptedException e) {}
            }

            datos[cola] = x;
            cola = (cola+1)%N;
            elems++;
            noVacio.signal();
        }
        finally {
            lock.unlock();
        }
    }

    // Método consumidor
    public int get() {
        try {
            lock.lock();
            while(elems == 0) {
                System.out.println("consumidor esperando...");
                try { noVacio.await(); }
                catch(InterruptedException e) {}
            }

            x = datos[cabeza];
            cabeza = (cabeza+1)%N;
            elems--;
            noLleno.signal();
        }
        finally {
            lock.unlock();
        }

        return x;
    }
}
```

## Executors

Con la interfaz **Executor**, Java nos ofrece un entorno para la creación y gestión de hilos con la que ejecutar taras de una forma muy flexible. Por ejemplo, con `SingleThreadExecutor` permite utilizar un solo hilo de trabajo que garantiza que las tareas se ejecutan de forma secuencial, y que no habrá más de una tarea activa en un momento dado. También ofrece *Thread-pools*, que permiten un conjunto de hilos (pool), e ir reutilizándolos para ejecutar diferentes tareas cada vez, previdiendo así el consumo desmedido de recursos.
