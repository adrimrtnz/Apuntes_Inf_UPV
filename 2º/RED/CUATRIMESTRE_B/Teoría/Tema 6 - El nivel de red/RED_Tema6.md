# Tema 6: El nivel de red

## 1. Introducción

El nivel de transporte se apoya en el **nivel de red** para llevar los segmentos desde el origen al destino a través de Internet. Es un protocolo para el diálogo en el nivel del red: **IP** (*Internet Protocol*).

### Servicios del nivel de red

Cuando la capa de transporte le pasa a la de red un paquete ¿qué puede esperar de ella?

* Servicios a nivel de paquete individual:
  * Entrega garantizada.
  * Entrega garantizada con retardo limitado.
* Servicios para un flujo de paquetes:
  * Entregar en orden.
  * Ancho de banda mínimo garantizado.
  * Fluctuación máxima garantizada.
  * Servicios de seguridad: Confidencialidad, integridad, autenticación, etc.

### Tipos de servicios

Existen los servicios orientados a la conexión o sin conexión:

**Servicio con conexión:** Antes de enviar paquetes de un ordenador a otro, hay que establecer una conexión a nivel lógico.

* Los routers intermediarios intervienen en el proceso.

**Servicio sin conexión:** redes de datagramas.

**Servicio con conexión en nivel de transporte vs. nivel de red:**

* Transporte: entre dos procesos.
* Red: entre dos host (routers se involucran).

### Redes de datagramas

> **Internet es una red de datagramas.**

Cuando se quiere enviar un paquete, simplemente se envía, poniéndole la dirección del destino en la cabecera.

Los routers no guardan estado de la conexión del nivel de transporte.

* A nivel de red no existe el concepto de "conexión".

Los paquetes se reenvían en los routers usando la dirección del host destino.

* Paquetes entre el mismo par origen-destino pueden seguir rutas diferentes.

### Requisitos para la comunicación

La unidad de intercambio común son los **paquetes** (datagramas IP). Para poder llevar los paquetes a través de la red se necesita:

* Identificar mediante direcciones a los sistemas que intervienen en la comunicación (**direcciones IP**).
* Elegir una ruta en la red que permita alcanzar el destino (**encaminamiento**).

El nivel de red se encarga de ambos problemas. Este nivel tiene **dos tareas**.

* **Forwarding (reenvio)**: Un router debe mover los paquetes recibidos desde el enlace de entrada al enlace de salida adecuado. Suelen emplearse **tablas de reenvío** .
* **Routing (enrutamiento)**: Calcula la ruta a tomar por los paquetes de origen a destino. Se calculan meciante **algoritmos de enrutamiento**.
* En ocasiones se emplea el término **encaminamiento** indistintamente para ambas tareas.

![image-20220224185921984](C:\Users\adri_\OneDrive\UPV\2º\RED\CUATRIMESTRE_B\Teoría\Tema 6 - El nivel de red\img\Tema6_01.jpg)



## 2. El protocolo IPv4

IP es el protocolo central de la pila de protocolos TCP/IP. La unidad básica de transferencia de datos es el **datagrama**. 

Es un servicio **"best effort"**:

* No fiable.
* Sin conexión:
  * No mantiene información de estado sobre los datagramas.
  * Cada datagrama se maneja independientemente.

IP realiza las funciones de encaminamiento y determina las reglas de intercambio de los datagramas enre computadores:

* Formato, reglas de procesamiento de datagramas, condiciones de error, etc.

#### Formato datagrama IP

![Formato de un datagrama IP](C:\Users\adri_\OneDrive\UPV\2º\RED\CUATRIMESTRE_B\Teoría\Tema 6 - El nivel de red\img\Tema6_02.jpg)

| Etiqueta                     | Descripción                                                  |
| ---------------------------- | ------------------------------------------------------------ |
| Versión del protocolo IP     | 4 bits, actualmente IPv4                                     |
| Longitud de la cabecera      | 4 bits, tamaño de la cabecera del datagrama en **palabras de 32 bits**. |
| Longitud total del datagrama | Incluye cabecera y datos. Tamaño máximo 65.535 bytes (64K - 1) |
| Tipo de servicio (TOS)       | 3 bits para la prioidad, 4 bits para el tipo de servicio y un bit a cero. Los bits de tipo de servicio permiten al usuario solocitar las condiciones deseadas, aunque no se garantiza el tipo de servicio solicitado. ![servicios](C:\Users\adri_\OneDrive\UPV\2º\RED\CUATRIMESTRE_B\Teoría\Tema 6 - El nivel de red\img\Tema6_03.jpg) |
| Fragmentación                | En el nivel de enlace cada protocolo maneja un tamaño máximo de trama, limitando el tamaño de su campo de datos: **MTU** (*Maximum Transfer Unit*) |
| Tiempo de vida (TTL)         | Los datagramas tienen un tiempo limitado de permanencia en Internet. El TTL se inicializa en origen y se decrementa cada vez que el datagrama atraviesa un router (valor inicial recomendado = 64). Al llegar a cero el datagrama se descarta. |

Se recomienda el uso de los siguientes valores para el tipo de servicio, dependiendo de la aplicación:

![recomendaciones de servicios - INFORMATIVO](C:\Users\adri_\OneDrive\UPV\2º\RED\CUATRIMESTRE_B\Teoría\Tema 6 - El nivel de red\img\Tema6_04.jpg)

#### Otros campos

El campo **protocolo** indica el protocolo al que corresponden los datos:

| Protocolo | Valor del campo protocolo |
| --------- | ------------------------- |
| TCP       | 6                         |
| ICMP      | 1                         |
| UDP       | 17                        |

  El **checksum** incluye sólo la cabecera. 

El campo de **opciones** se utiliza raramente. Tiene longitud variable y permite especificar:

* Encaminamiento fuente (uso de una ruta escogida).
* Confidencialidad del datagrama.
* Registro de la ruta (RR).
* etc.

## 3. El protocolo IPv6

## 4. Algoritmos de enrutamiento

La función encargada del algoritmo de enrutamiento en un router se comunica con la función correspondiente en otros routers para calcular los valores con los que rellenar su tabla de reenvío.

En las **redes SDN** (*Software-Defined Networking*) se dice que la red está "definida por software" porque el controlador que calcula las tablas de reenvío y que interacciona con los routers está implementado en software.

## 5. Enrutamiento en Internet

### OSPF

### BGP

