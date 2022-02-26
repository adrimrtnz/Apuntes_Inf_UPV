# Tema 3: Primitivas de sincronización

## Concepto de Monitor

> **Monitor:** clase para definir objetos que podemos compartir de forma segura entre distintos hilos.

Proporciona abstracción:

* El programador que invoca operaciones sobre el monitor ignora cómo se implementan.
* El programador que implementa el monitor ignora cómo se usa.

Con la utilización de monitores:

* Los hilos se coordinan mediante objetos compartidos.
* Se ocultan los detalles de exclusión mutua y sincronización en las clases que representan los objetos compartidos.
* Simplifica el desarrollo y mantenimiento.
* Mejora la documentación y legibilidad.
* Facilita la depuración.

## Monitores en Java

Todo objeto posee de forma implícita (sin necesidad de declararlos):

* Un **lock**:
  * Al etiquetar un método con `synchronized`, se garantiza ejecución en exclusión mutua. Equivale a *cerrar lock* antes de su primera instrucción y *abrir lock* tras la última.
* Una sola cola de espera con primitivas:
  * `wait()`: espera sobre la cola de espera.
  * `notify()`: reactiva a uno de los hilos que esperan en dicha cola.
  * `notifyAll()`: reactiva a todos los que esperan.

Pero **no** podemos declarar otros locks ni otras colas de espera.

Una clase que defina objetos a compartir entre hilos debería:

* Definir todos sus atributos como `private`.
* Sincronizar todos sus métodos no privados con `synchronized`.
* En la implementación de cada método, acceder sólo a atributos de la clase y variables locales (definidas en el propio método).
* Utilizar `wait()`, `notify()`, `notifyAll()` dentro de los métodos sincronizados.

> **Nota**: No hay ningún tipo de aviso ni error si hay atributos no privados, o métodos públicos sin la palabra `synchronized` o se utiliza `wait()`, `notify()`, `notifyAll()` en un método no sincronizado (Es responsabilidad del programador).

En un monitor ideal los hilos que esperan por condiciones lógicas distintas esperan en colas de espera distintas. Sin embargo, Java utiliza únicamente una variable condición por monitor:

* La biblioteca `java.util.concurrent`resuelbre esa limitación.
* Los hilos que esperan por condiciones lógicas distintas esperan en una única cola, no en colas diferentes.
* Al reactivar un hilo no sabemos si reactivamos al que esperaba por una condición o por otra
  * Excepto en casos muy simples, se recomienda despertar a todos y que cada uno vuelva a comprobar su condición.

## Variantes de monitor

Cuando en un monitor se reactiva un hilo suspendido en una condición surge un problema, ya que se pasaría a tener dos hilos activos dentro de un mismo monitor: el invocador (o notificador) y el que se ha reactivado (o ha sido notificado). Esto rompería la exclusión mutua que los monitores garantizan. Por ello, todo monitor debe mantener suspendido temporalmente a uno de los dos hilos. Se explican diversas variantes de monitor, **Hoare**, **Lampson-Redell** y **Brinch-Hansen**.

### Monitor Brinch-Hansen

> El hilo N (notificador) abandona el monitor

La sentencia *notify* es obligatoriamente la última sentencia del método. Esta solución no puede aplicarse siempre:

* Algunos problemas complejos requieren realizar otras acciones tras `a.notify()`.

### Monitor Hoare

> El hilo N (notificador) espera en una **cola especial**.

Elimina la restricción de Brinc-Hansen, por lo que se ve obligada a utilizar una cola especial de reentrada al monitor, donde colocará temporalmente al hilo notificador. Este hilo en la cola especial tiene prioridad sobre aquellos hilos que se hayan suspendido en la cola de entrada. El hilo reactivado entra en el monitor.

### Monitor Lampson-Redell

> El hilo W (notificado) espera en la entrada.

Da prioridad al hilo notificador. El hilo que debe reactivarse va a la cola de entrada, compitiendo con aquellos hilos que también quieran acceder al monitor. El hilo N queda activo en el monitor.

Cuando W (hilo notificado) consiga entrar, el estado puede haber cambiado de nuevo, por lo que hay que **reevaluar** la condición.
