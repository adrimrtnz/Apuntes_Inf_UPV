# Unidad temática 2: Concepto de Llamada al Sistema

## LLamadas al Sistema

## Interrupción
El Sistema Operativo es un programa dirigido por eventos. Estos eventos son la **interrupciones hardware**, las **interrupciones software** y las **excepciones**. 
* El SO actúa como un programa servidor a la espera de que le soliciten trabajo mediante interrupciones.
* Los procesos y dispotivos de E/S solicitan servicios al SO.

Se pueden dar tres clases de acciones:
* Atender.
* Ignorar.
* Enmascarar: Atenderla luego.

> Completar con diapos Tema 2 (Pg. 10)

## Modos de ejecución del procesador
Se puede limitar el acceso de los usuarios a diferentes acciones y/o opciones del procesador. Los procesadores modernos tienen (al menos) dos modelos:
* **Modo Nucleo(0)**: es el modo privilegiado que te permite hacer cualquier cosa.
* **Modo Usuario(1)**: más restrinctivo y más utilizado.

Los modos de ejecución se  incluyen para dar soporte al SO. Los procesos que se ejecutan simultáneamente comparten recursos de la máquina $\rightarrow$ **necesitan protección**.

## Concurrencia
Es la ejecución de varias tareas intercaladas entre ellas haciendo posible que el usuario perciba que la máquina está realizando varias operationes o tareas de forma simultanea. La máquina va cambiando de una a otra de forma muy rápida para conseguir esta *ilusión*.
* **Dipositivos de E/S (I/O)**: más lentos que los procesadores.
* **CPU**: una CPU moderna es capaz de ejecutar miles de millones de instrucciones máquina en el tiempo que se requiere para acceder al disco.
    * Mientras se realizan operaciones de E/S el procesador debe poder ejecutar simultáneamente instrucciones útiles.

## Utilidades del sistema operativo
* Se ejecutan como procesos de usuario y proporcionan un **entorno más cómodo** de trabajo.
* Se proporcionan como parte del OS, pero no son imprescindibles para el funcionamiento de la máquina.

## Identidades
