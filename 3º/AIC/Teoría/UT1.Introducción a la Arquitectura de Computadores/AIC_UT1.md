# Unidad 1: Introcucción a la Arquitectura de computadores

## Tema 1.1
### 1.1: Concepto de Arquitectura de computadores

### 1.2: Requisitos de un computador

### 1.3: Tecnología, consumo y coste

### 1.4: Evolución del rendimiento de los procesadores
* Es difícil sacar provecho de múltiples cores.
* La situación actual es tener el máximo número de cores y explotarlos y/o tener una arquitectura específica para un problema específico que aproveche al máximo esos cores en ese problema en particular.
* Un solo procesador sofisticado es mucho mejor que n cores, pero tendría grandes problemas energéticos y de disipación.

### 1.5: Clases de computadores
* **Mainframes**: grandes computadores, caros y solamente accesibles a grandes corporaciones.
* **Minicomputers**: computadores de tamaño medio, muy utilizados en universidades.
* **Personal Mobile Devices (PMD)**: aquí están los *smartphones*, tablets, PDAs, etc.
* **Sistemas empotrados**: electrónica diversa, sistemas embebidos de automoción y aeronáutico, electrodomésticos, etc.
* **Computadores personales**: sobremesa, portátiles, netbooks.
* **Servidores**.
* **Clusters** y clusters a gran escala.
* **Supercomputadores**.

## Tema 1.2
En esta parte se ven las dos principales ecuaciones que vamos a gastar para todo.

### 2.1: Definición de presteciones
$$
T_{ejecución} = \frac{seg}{programa} = \frac{núm.instr.}{programa} \times \frac{ciclos}{num-instr.} \times \frac{seg}{ciclo} = I \times CPI \times T
$$

### 2.2: Principios cuantitaivos del diseño de computadores
La **Ley de Amdahl** describe cómo afecta el cambio de una parte de un proceso en el total.
* **F** es la fracción de tiempo que cambia.
* **S** es la aceleración que se aplica a esa fracción.

La **relación prestación-coste** mide la relación entre las prestaciones alcanzadas y el coste de una configuración data. El cambio en el coste vendría especificado, de forma bastante simple, como:

$$
\Delta C = \frac{C_{Nuevo}}{C_{Original}}
$$

En el momento en que el aumento en prestaciones (aceleración que se obtiene) supera el aumento en coste, el cambio vale la pena.

$$
S' \ge \Delta C
$$

### 2.3: La medida de prestaciones

### 2.4: Otras medidas de prestaciones


## Tema 1.3: Diseño de los juegos de instrucción
> No le compiles la vida al tío del compilador

---

## Ejercicios
> El ejercicio de la ley de Amdahl suelen ser el primero del examen.

### Ejercicio 1.3

### Ejercicio 1.5
Este ejercicio es engañoso. Recordar que **F** tiene que indicar porcentaje de tiempo, no el porcentaje de instrucciones.

$$
CPI_{Enteros} = 1 \\
CPI_{CF} = 5 \\
\Delta C = 2 \\
S_{CF} = 5 \\[20px]
$$

$$
T_{eje} = I \times CPI \times T =\\[5px]
 = \frac{I \times (0,8\times 1 + 0,2 \times 5) \times T}{I \times (0,8\times 1 + 0,2 \times 1) \times T} = 1,8
$$

### Ejercicio 1.6
Hay que calcular F.

* Tiempo Ejecución: 
    * 1 min con coprocesador.
    * 2.5 min sin coprocesador.

$$
S'= \frac{1}{1-F+\frac{F}{S}} = 2.5 \\[10px]
\text{Despejando para F} \rightarrow 
F = \frac{0.6}{0.8} = 0,75 = 75\%
$$

### Ejercicio 1.9
1. RAID
$$
S_D'=\frac{120s}{80s} \approx 1.4286 = 42.86\% \\[10px]
\Delta C_D = \frac{300+90}{300} = \frac{390}{300} = 1,3
$$

Como el aumento en la aceleración es mayor que el aumento en el coste, es rentable.

2. GPU
$$
S_G=3 \\[10px]
F_G= 30\% = 0.3 \\[10px]
S_G'=\frac{1}{1-F_G +\frac{F_G}{S_G}} = \frac{1}{0.7+0.1} =1.25 \\[10px]
\Delta C_G = \frac{300+125}{300} = \frac{425}{300} = 1,42
$$

En este caso no sale rentable.

3. Qué debería hacer costado el computador original...

$$
S_{D+G}' = \frac{1}{1-F_D-F_g+\frac{F_D}{S_D}+\frac{F_G}{S_G}} \\[10px]
S_D = \frac{1}{0.4} = 2.4 \\[10px]
$$

Falta calcular $F_D$ y resolver $S_{D+G}'$ y de ahí igualar $\Delta C = \frac{C+90+125}{C}$ a la aceleración total y despejar $C$.