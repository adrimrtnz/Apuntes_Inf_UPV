# Tema 1: Introducción a las redes de computadores e Internet

![chapter1-img-header](https://www.nicepng.com/png/full/116-1167391_7-caractersticas-de-internet-y-las-redes-sociales.png)

## Capítulo 1: Introducción
> 1. ¿Qué es Internet?
> Las palabras importantes serían **red** e **interconexión**.
> Usualmente se define internet como una red de redes interconectadas.

Internet lo forman cientos de millones de dispositivos informáticos conectados.

* Host: sistemas terminales (ordenadores, móviles, dispositivos IoT, etc.).
* Enlaces de comunicaciones:
    * Medios físicos: Fibra, cobre, enlaces de radio.
    * Proporcionan distinta vel. de transmision.
* Routers: reenvio de paquetes de datos (los host dividen sus datos en paquetes y los envían).
* ISP (Internet Service Provider): el ISP de las universidades públicas es la RedIRIS.

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

Existen diferentes **estándares de internet**:
* Sirven para crear productos que puedan interoperar.
* Se llaman **RFC** (Request for comments).
* Los desarrolla el **IETF** (Internet Engineering Task Force).
* Hay otros estándares de red, como por ejemplo, a nivel de enlace, el comité IEEE 802.
