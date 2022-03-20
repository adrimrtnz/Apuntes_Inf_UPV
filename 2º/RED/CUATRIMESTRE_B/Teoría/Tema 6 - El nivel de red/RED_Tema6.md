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

![image-20220224185921984](.\img\Tema6_01.jpg)

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

![Formato de un datagrama IP](.\img\Tema6_02.jpg)

| Etiqueta                     | Descripción                                                                                                                                                                                                                                                                                                                            |
| ---------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Versión del protocolo IP     | 4 bits, actualmente IPv4                                                                                                                                                                                                                                                                                                               |
| Longitud de la cabecera      | 4 bits, tamaño de la cabecera del datagrama en **palabras de 32 bits**.                                                                                                                                                                                                                                                                |
| Longitud total del datagrama | Incluye cabecera y datos. Tamaño máximo 65.535 bytes (64K - 1)                                                                                                                                                                                                                                                                         |
| Tipo de servicio (TOS)       | 3 bits para la prioidad, 4 bits para el tipo de servicio y un bit a cero. Los bits de tipo de servicio permiten al usuario solocitar las condiciones deseadas, aunque no se garantiza el tipo de servicio solicitado. ![servicios](.\img\Tema6_03.jpg) |
| Fragmentación                | En el nivel de enlace cada protocolo maneja un tamaño máximo de trama, limitando el tamaño de su campo de datos: **MTU** (*Maximum Transfer Unit*)                                                                                                                                                                                     |
| Tiempo de vida (TTL)         | Los datagramas tienen un tiempo limitado de permanencia en Internet. El TTL se inicializa en origen y se decrementa cada vez que el datagrama atraviesa un router (valor inicial recomendado = 64). Al llegar a cero el datagrama se descarta.                                                                                         |

Se recomienda el uso de los siguientes valores para el tipo de servicio, dependiendo de la aplicación:

![recomendaciones de servicios - INFORMATIVO](.\img\Tema6_04.jpg)

#### Otros campos

El campo **protocolo** indica el protocolo al que corresponden los datos:

| Protocolo | Valor del campo protocolo |
| --------- | ------------------------- |
| TCP       | 6                         |
| ICMP      | 1                         |
| UDP       | 17                        |

> El número de protocolo es el elemento que enlaza las capas de red y de transporte, mientras que el número de puerto es el componente que enlaza las capas de transporte y de aplicación.

El **checksum** incluye sólo la cabecera. 

El campo de **opciones** se utiliza raramente. Tiene longitud variable y permite especificar:

* Encaminamiento fuente (uso de una ruta escogida).
* Confidencialidad del datagrama.
* Registro de la ruta (RR).
* etc.

#### Direccionamiento CIDR (Classless Inter-Domain Routing)

Cuando hay que encaminar un datagrama, para averiguar la ruta se sigue el proceso siguiente de reenvío:

1. Para cada línea de la tabla de encaminamiento, se realiza un AND lógico entre la **dirección IP destino** del datagrama y la **máscara de res**. IP conpara el resultado con la **Red Destino** y marca todas las rutoas en las que se producen coincidencia.

2. De la lista de rutas coincidentes IP selecciona la ruta que tiene más bits en la mascara. Esta es la ruta más específica y se conoce como la **ruta de máxima coincidencia** (*longest matching*).

3. Si hay varias rutas de máxima coincidencia, se usa la ruta con menor **métrica**. Si hay varias con la misma métrica se usa una cualquiera de ellas.

> Una **métrica** es un valor que se asigna a una ruta IP para una interfaz de red determinada. Identifica el costo asociado al uso de esa ruta. Por ejemplo, la métrica se puede valorar en términos de velocidad de vínculo, recuento de saltos o retraso de tiempo[^1].

[^1]: [La característica Métrica automática para rutas IPv4 - Windows Server | Microsoft Docs](https://docs.microsoft.com/es-es/troubleshoot/windows-server/networking/automatic-metric-for-ipv4-routes#:~:text=Una%20m%C3%A9trica%20es%20un%20valor,saltos%20o%20retraso%20de%20tiempo.)

## 3. El protocolo IPv6

## 4. Algoritmos de enrutamiento

La función encargada del algoritmo de enrutamiento en un router se comunica con la función correspondiente en otros routers para calcular los valores con los que rellenar su tabla de reenvío.

En las **redes SDN** (*Software-Defined Networking*) se dice que la red está "definida por software" porque el controlador que calcula las tablas de reenvío y que interacciona con los routers está implementado en software.

En los algoritmos de enrutamiento la red se representa mediante un grafo:

* **Vértices** del grafo son los **routers**.
* **Aristas** del grafo son los **enlaces del router**.

### Criterios para la clasificación de algoritmos

Dos cuestiones fundamentales sobre el algoritmo de enrutamiento:

* **Escalabilidad**: Algoritmos por vector de distancias y estados del enlace como máximo para 100 routers.
* **Centralizado o distribuido**: Depende de dónde se calculen las tablas. Los algoritmos centralizados son difíciles de escalar, todas nuestras propuestas serán de **algoritmos distribuidos**.

Como otro criterio para la clasificación se pueden dividir dependiendo de la frecuencia de actualización de rutas:

* **Estáticos**: suelen actualizarse manualmente.
* **Dinámicos**: son sensibles a cambios en el tráfico o en la topología de la red.

Los algoritmos de enrutamiento empleados en **Internet** suelen ser **dinámicos**.

### 4.2 Enrutamiento por estado del enlace

### 4.3. Enrutamiento por Vector de Distancia

### Comparación de ambos enrutamientos

> Extraido de Kurose

**Complejidad del mensaje:** El algoritmo de *Estado del enlace* requiere que cada nodo conozca el coste de cada enlace de la red. Cuando los costes de los enlaces cambian, el algoritmo de vector de distancia popagará los resultados del  coste del enlace que ha cambiado sólo si el nuevo coste de enlace da lugar a una ruta de coste mínimo distinta para uno de los nodos conectados a dicho enlace.

**Velocidad de convergencia:** El de estado de enlace tiene un coste de $O(N^2)$  que requiere enviar $O(N \cdot E)$ mensajes. El algoritmo de vector de distancia puede converger lentamente y pueden aparecer bucles de enrutamiento mientras está convergiendo. Este algoritmo también subre el problema de la cuenta hasta infinito.

**Robustez:** En estado de enlaces, un router podría difundir un coste incorrecto para uno de sus enlaces conectados (pero no para todos). Con este algoritmo un nodo solo calcula so propia tabla de reenvío, mientras que otros nodos realizan cálculos similares por sí mismos. Esto significa que los cálculos de rutas son hasta cierto punto independientes en *Estado del Enlace*, porporcionando mayor grado de robustez.

## 5. Enrutamiento en Internet

### Open Shortest Path First (OSPF)

> Protocolo de enrutamiento interno del sistema autónomo

### Border Gateway Protocol (BGP)

> Protocolo de enrutamiento entre sistemas autónomos

BGP es un protocolo descentralizado y asíncrono, en la línea del enrutamiento por vector de distancia. 

En BGP, los paquetes no se enrutan hacia una dirección de destino específica, sino hacia prefijos CIDR (Classless Inter-Domain Routing).

Como protocolo de enrutamiento entre sistemas autónomos, BGP proporciona a cada router mecanismos para:

1. Obtener de los sitemas autónomos vecinos información acerca de la alcanzabilidad de los prefijos.

2. Determinar las "mejores" rutas hacia los distintos prefijos.

En un sistema autónomo, cada router puede ser:

* **Router de pasarela:** aquel que está situado en la frontera de un sistema autónomo y se conecta directamente a uno o más routers de otros sistemas autónomos.

* **Router interno:** solamente está conectado a hosts y routers pertenecientes a su propio sistema autónomo.
