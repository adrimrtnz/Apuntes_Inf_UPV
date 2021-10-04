# Tema 1: Introducción a las redes de computadores e Internet

![chapter1-img-header](https://www.nicepng.com/png/full/116-1167391_7-caractersticas-de-internet-y-las-redes-sociales.png)

## Capítulo 1: Introducción
> 1. ¿Qué es Internet?
> Las palabras importantes serían **red** e **interconexión**.
> Usualmente se define internet como una red de redes interconectadas.

Internet lo forman cientos de millones de dispositivos informáticos conectados.

* **Host**: sistemas terminales (ordenadores, móviles, dispositivos IoT, etc.).
* Enlaces de comunicaciones:
    * Medios físicos: Fibra, cobre, enlaces de radio.
    * Proporcionan distinta vel. de transmision.
* **Routers**: reenvio de paquetes de datos (los host dividen sus datos en paquetes y los envían).
* **ISP (Internet Service Provider)**: el ISP de las universidades públicas es la RedIRIS.

### Medios físicos
* Medio guiado:
* Cable coaxial: dos conductores de cobre concénctricos.
    * Originalmente empeado en Ethernet como medio compartido (banda base).
    * Se sigue empleando en TV (banda ancha).
* Cable fibra óptica: fibra de vidrio con pulsos de luz, cada pulso es un bit.
    * Alta velocidad (cientos de Gbps).
    * Poca atenuación (cientos de km).
    * Baja tasa de errores.
    * Inmune al ruido electromagnético.
* Radio:
    * Señal transportada en el espectro electromagnético.
    * No hay "cable" físico.
    * Efectos del ambiente de propagacion.
        * Interferencias.
        * Reflexión (la señal también llega "rebotada").
        * Obstrucción por objetos.

### Componentes esenciales
Los **protocolos** controlan el envío y recepción de mensajes y su formato. Se implementan en los *host* y en los nodos de conmutación. Para cada tipo de comunicación se utiliza, en ocasiones, protocolos específicos para ese tipo de información.
* Se invían mensajes específicos (según lo que se pretende).
* Se indican a las acciones a tomar según mensajes recibidos.

El protocolo define el formato y el orden de los mensajes intercambiados entre entidades en la red, y las acciones adoptadas al producirse la transmisión y/o la recepción de un mensaje.

Existen diferentes **estándares de internet**:
* Sirven para crear productos que puedan interoperar.
* Se llaman **RFC** (Request for comments).
* Los desarrolla el **IETF** (Internet Engineering Task Force).
* Hay otros estándares de red, como por ejemplo, a nivel de enlace, el comité IEEE 802.

Existen dos versiones del **protocolo IP**, una de 32bits (IPv4), y la más nueva de 128bits (IPv6). En IPv6 cada byte se expresa con dos dígitos hexadecimales.

### Servicios que proporciona
Internet como infraestructura que proporciona servicios de comunicaciones a las aplicaciones (distribuidas):
* Clásicas (web, email, ftp) y más recientes (juegos, OOT).
* Las aplicaciones están en el host (no routers).

Servicios que proporciona Internet a las aplicaciones:
* Entrega de datos fiables del origen al destino (TCP).
* Entrega de datos "best effort" no fiable (UDP).

### Acceso a Internet con Ethernet

### Núcleo de la red
Formado por una malla de routers interconectados. Existen dos alternativas en la transferencia de datos por una red:
1. **Conmutación de circuitos**: los recursos **se reservan** durante el tiempo que dura la sesión entre dos host. 
    * En la conmutación de circuitos no estás conmutando un circuito real, es una **multiplexación por división en el tiempo** (o por división en la frecuencia).

![FDM-TDM](https://image1.slideserve.com/2973657/circuit-switching-fdm-and-tdm-n.jpg)

2. **Conmutación de paquetes**: los recursos se utilizan **bajo petición**, si no están disponibles hay que esperar.
    * Cada flujo de datos de extremo a extremo se divide en paquetes.
    * Al enviar un paquete, utiliza el ancho de banda completo del enlace (sin circuitos).
    * Los recursos se usan conforme se necesitan.
    * La demanda agregada de recursos puede exceder la cantidad disponible.
    * Congestión: cola de paquetes (buffer), espera para uso de enlaces.

En este tipo de conmutación el **retardo de transmisión** depende de la velocidad de transmisión del enlace $(V_{trans} \sim b/s)$ y de la longitud del paquete $(L \sim bits)$.

$$
T_{trans} = \frac{L}{V_{trans}}
$$

¿Cuánto tardamos en inyectar un paquete de L bits en una red de Rbps?

$$
R = \frac{L}{t_{trans}}
$$

### Estructura de internet
Es más o menos jerárquica. En el centro existen unos pocos ISPs de grandes redes (cobertura nacional e internacional. **Redes Troncales**).
* ISPs comerciales de "nivel-1" (tier-1) + Grances distribuidores de contenidos (Goole, Akamai, Microsoft).
* Se tratan entre sí como iguales (intercambio de datos gratis, acuerdo entre iguales $\rightarrow$ *peering*).
* Los ISPs de Nivel-3 son ISPs locales.
    * Son clientes de las redes de Nivel-1 y Nivel-2.
    * **Redes/ISP de acceso** (last hop) a las que se conectan los host de los usuarios.

### Retardos, pérdidas y tasa de transferencia (throughput) en redes de conmutación de paquetes
![Throughput](https://cdn.comparitech.com/wp-content/uploads/2019/01/DiagramLatency-vs-throughput-2-1024x427.jpg)

Si la tasa de llegada de paquetes al enlace excede la capacidad de salida del enlace los paquetes se encolan, esperando su turno.

El **Throughput extremo a extremo** es la tasa a la que los bits son recibidos entre el destino.
* **Instantaneo**: tasa en un momento dado.
* **Medio**.


Existen 4 fuentes en el retardo de los paquetes:
* **Tiempo de procesamiento** (procesamiento del nodo):
    * Comprobación de errores.
    * Determinar enlace de salida.
    * Del orden de microsegundos.
* **Tiempo de cola** (retardo de cola):
    * Tiempo de espera en enlace de salida para la transmisión.
    * Depende del nivel de congestión del router.
    * *Diapos 1-43*.
* **Tiempo de transmisión**:
* **Tiempo de propagación**:
    * Tiempo que tarda la señal en transmitirse en el medio en el que lo hace.
    * Lo más influyente es la distancia de un punto a otro.
    * **RTT** (**R**ound **T**rip **T**ime): tiempo en milisegundos desde que un navegador manda la petición hasta que recive una respuesta desde el servidor

### Capas de protocolos, modelos de servicio

#### Modelo de referencia ISO/OSI
Permite interpretar el significado de los datos. La **sesión** delimita y sincroniza el intercambio de datos. La pila de Internet no tiene estas capas, si una aplicación necesita estos servicios, debe implementarlos.

|Capas|
|:--------:|
|Aplicación|
|Sesión|
|Transporte|
|Red|
|Enlace|
|Física|

