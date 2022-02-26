# Tema 1: Introducción a la Programación Concurrente

## Concepto de Programación Concurrente

Hay que diferenciar entre programa secuencial (una única actividad - flujo de control único) y un **programa concurrente** que es:

* Una **colección de actividades** (hilos) que pueden ejecutarse en paralelo.

* Y **cooperan** para llevar a cabo una tarea común.

### **¿Cómo obtener la concurrencia?**

Se puede conseguir de dos formas:

* **Paralelismo lógico:** un procesador con multiprogramación.

* **Paralelismo real**: varios procesadores (varios núcleos).

Aunque también se pueden combinar ambos tipos de paralelismos.

### Ventajas e Inconvenientes de la Programación Concurrente

| Ventajas                          |                                                                                          |
|:--------------------------------- |:----------------------------------------------------------------------------------------:|
| **Eficiencia**                    | Explota mejor los recursos máquina                                                       |
| **Escalabilidad**                 | Puede extenderse a sistemas distribuidos                                                 |
| **Gestión de las comunicaciónes** | Explota la red. Facilita el solape entre actividades de red y resto de actividades.      |
| **Flexibilidad**                  | Resulta más fácil adaptar el programa a cambios en la especificación.                    |
| **Menor hueco semántico**         | En aquellos problemas que se definen de forma natural como una colección de actividades. |

Las consecuencias de las ventajas anteriores son:

* Mejora de prestaciones y tolerancia a fallos. Útil en:
  
  * Sistemas Operativos.
  
  * Sistemas de Gestión de Bases de Datos.
  
  * Software científico de muy elevadas prestaciones.

* Mejora la interactividad y flexibilidad:
  
  * Sistemas cliente/servidor, uso internet (ej. P2P).
  
  * Dispositivos móviles.
  
  * Modelo de programación cercano al problema real (Sistemas de tiempo real, control de procesos, etc.).

| Inconvenientes            |                                                                                                     |
| ------------------------- | --------------------------------------------------------------------------------------------------- |
| **Programación delicada** | Hay que conocer los problemas potenciales, como las **Condiciones de Carrera** o **Interbloqueos**. |
| **Depuración compleja**   | No determinismo                                                                                     |

## Creación de hilos en Java

Se puede hacer **Implementando la interfaz Runnable**:

```java
public class HolaRunnable implements Runnable {
    public void run() {
        System.out.println("Hola máquina!")
    }

    public static void main(String... args) {
        (new Thread(new HolaRunnable())).start();
    }
}
```

O también **Extendiendo la clase Thread**:

```java
public class HolaThread extends Thread {
    public void run() {
        System.out.println("¿Qué pasa cabesa?");
    }

    public static void main(String... args) {
        (new HolaThread()).start();
    }
}
```

La ejecución del hilo arranca con `start()` que ejecuta el código del método `run()`.

Un error típico es invocar a `run()` en lugar de `start()`, lo que lanzaría a ejecución el código de `run()` pero de forma secuencial, perdiendo la concurrencia (todas las instrucciones serían ejecutadas por el hilo `main`).

### Pausar la ejecución de un hilo con `sleep()`

`Thread.sleep(long millis)` causa la suspensión de la ejecución del hilo por el tiempo indicado (en milisegundos).

Este método lanza la excepción `InterruptedException` cuando el hilo suspendido es interrumpido por otro hilo.

```java
try {
    Thread.sleep(4000);
} catch(InterruptedException e) {
    System.out.println("Caught InterruptedException: " + e.getMessage());
}
```

## Notación Lambda

Las expresiones Lambda son funciones anónimas, y pueden ser utilizadas donde el tipo aceptado sea una interfaz funcional (interfaz con un solo método abstracto).

>  La interfaz Runnable es una interfaz funcional con un único método abstracto `run()`.

Su sintaxis básica: `(parámetros) -> { cuerpo }`

* El operador lambda (->) separa la declaración de parámetros de la declaración del cuerpo de la función.

* **Parámetros:** Cuando no se tienen parámetros, o cuando se tienen dos o más, es necesario utilizar paréntesis.

* **Cuerpo:** Cuando el cuerpo de la expresión lambda tiene una única línea no es necesario utilizar las llaves.

```java
// Implementación estándar
Runnable task1 = new Tunnable() {
    public void run() {
        System.out.println("Hilo #1");
    }
}

// Implementación con Notación Lambda
Runnable task1 = () -> { System.out.println("Hilo #1"); };
// == Runnable task1 = () -> System.out.println("Hilo #1");
```
