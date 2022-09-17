# T1 - Introdución a la computación paralela

Existen dos tipos de planteamiento:
* Memoria compartida:
    * Todos los procesadores pueden acceder a toda la memoria.
    * Latencias distintas alacceder a los diferentes bancos de memoria (por proximidad).
    * Escalabilidad hasta cientos de procesadores.
    * Alto coste; alto rendimiento en paralelismo de grano fino.

* Memoria distribuida:
    * Cada procesador solo tiene acceso a parte de la memoria.
    * Intercambian información explícitamente con mensajes.
    * Escalabilidad mayor (miles de procesadores)
    * Coste más reducido; peor rendimiento en grano fino.

## Taxonomía de Flynn

* **SISD**: Single Instruction, Single Data.
* **SIMD**: Single Instruction, Multiple Data.
* **MISD**: Multiple Instruction, Single Data. No hay máquinas en este grupo ahora mismo, podemos olvidar este grupo.
* **MIMD**: Multiple Instruction, Multiple Data.

## Arquitecturas de Memoria Compartida

* **UMA**: Uniform Memory Access.
* **NUMA**: Non-Uniform Memory Access.
* **cc-NUMA**: Cache Coherent NUMA.

Tiene una **fácil programación** pero la escalabilidad es dificial y cara.

## Arquitectura de Memoria Distribuida
// TODO
