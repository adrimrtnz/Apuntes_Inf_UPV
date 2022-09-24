# Tema 3: Arquitectura del Software

## Objeticos
* Introducir el concepto de arquitectura del sistema.
* Describir las principales características de la **arquitectura multicapa**.

## Introducción

> Programming in the small/medium/large

* Cuando los sistemas software crecen en tamaño, se requiere una organización de los mismo en subsistemas que los hagan manejables.
* A lo largo de la historia del desarrollo de software se han utilizado diferentes **estrategias para manejar la complejidad**, generalmente relacionadas con el diseño a diferentes niveles de abstracción.
    * Módulos (métodos estructurados).
    * Clases (métodos orientados a objetos).
    * etc.

**Problemas:**
* Estas aprocimaciones son de bajo nivel, son meras agrupaciones de código.
* Se requiere un mecanismo más abstracto, que separe la aplicación en bloques funcionales.

## Arquitectura del software

> "*La **arquitectura de software**, tiene que ver con el diseño y la implementación de estructuras de software de alto nivel. Es el resultado de ensablar un cierto número de elementos arquitectónicos de forma adecuada para satisfacer la mayor funcionalidad y requerimientos no funcionales, como la confiabilidad, escalabilidad, portabilidad y disponibilidad.*"
(Kruchten, Philippe)

* En la etapa de descripción de la **Arquitectura del Sistema** debemos dotas al sistema de una organización global en **subsistemas**.

### Tipos de sistemas
* **Sistemas Distribuidos:** El sistema software en el que el procesamiento de información se distribuye sobre varias computadoras en vez de estar confinado en una única máquina.

* **Sistemas personales:** No son distribuidos y están diseñados para ejecutarse en un ordenador personal o estación de trabajo.

* **Sistemas Empotrados:** Sistemas informáticos (hardware + software), usualmente de tiempo real, integrados en un sistema de ingeniería más general, en el que realizan funciones de control, procesamiento y/o monitorización.

### Arquitecturas de Sistemas Distribuidos (entre otras)

* **Arquitectura Multi-Procesador:** El sistema consta de múltiples procesos que pueden (o no) ejecutarse en diferentes procesadores.

* **Arquitectura Cliente/Servidor:** El sistema puede ser visto como un conjunto de servicios que se proporcionan a los clientes por parte de los servidores. Los servidores y los clientes se tratan de forma diferente.

* **Arquitectura de objetos distribuidos:** El sistema puede ser visto como un conjunto de objetos que interaccionan y cuya localización es irrelevante. No hay distinción entre un proveedor de servicios y el usuario de estos servicios.