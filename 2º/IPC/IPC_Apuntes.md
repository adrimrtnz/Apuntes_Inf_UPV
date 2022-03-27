# 1. Introducción a las Interfaces Persona Computador

## Objetivos

* Valorar el peso de las interfaces de usuario como motores de la popularización de la tecnología.

* Conocer el concepto de Interfaz persona-computador.

* Recnocer la importancia de un buen interfaz y los problemas provocados por un mal interfaz.

* Conocer la evolución de las interfaces gráficas de usuario, desde los primeros sistemas interactivos vectoriales a las interfaces actuales.

* Conocer el origen de la interfaz basada en ventanas, iconos, menús y dispositivo apuntador.

## Introducción

Avances en el diseño de interfaces de usuario han popularizado el uso de los ordenadores.

* Inicialmente, el objetivo era aplicaciones de escritorio potentes, con muchas características y que aprovecharan los recursos de la máquina.

* Luego, la potencia extra de los ordenadores se usó para mejorar las interfaces, con aplicaciones más accesibles.

* Ahora el interés está en facilitar que el usuario comparta contenido.

* El siguiente paso es permitir a los dispositivos móviles acceder a dicha información.

La interacción persona-computador (*human-computer interaction*) es una disciplina que apolica técnicas de la psicología experimental a la informática y usa métodos de:

* Psicología industrial, diseño gráfico y diseño educativo, escritores técnicos, expertos en factores humanos y ergonomía, arquitectos de la información, antropólogos y sociólogos.

El resultado más visible ha sido la generación de las herramientas sociales que ahora estudian analistas de políticas, defensores de la propiedad intelectual, protectores de la intimidad, defensores de los consumidores y los profesionales de la ético.

* **Usuario:** persona que interacciona con un sistema informático.

* **Interacción:** Todos los intercambios que suceden entre usuario y el ordenador.

* **IPO (Interacción Persona-Ordenador):** Disciplina relacionada con el diseño, implementación y evaluación de sistemas informáticos interactivos para su uso por seres humanos.

Las interfaces de usuario efectivas tienen un gran impacto en la sociedad:

* Los doctores pueden diagnosticar mejor.

* Los pilotos pueden volar de forma más segura.

* Los niños pueden aprender más.

* Usuarios afectados con alguna discapacidad pueden llevar vidas más productivas.

* etc.

Por otro lado, interfaces deficientes provocan frustación, miedo o errores.

**Ciclo de vida clasíco para el desarrollo de programas:**

<img src="file:///C:/Users/adri_/OneDrive/UPV/2º/IPC/img/life-cycle.PNG" title="" alt="life-cicle" data-align="center">

**Iteraciones para el desarrollo de la interfaz de usuario:**

<img src="file:///C:/Users/adri_/OneDrive/UPV/2º/IPC/img/iterations.PNG" title="" alt="" data-align="center">

Los diseños de las interfaces deben facilitar la transición entre el gran rango de tamaños de pantalla:

* Móviles.

* Tablets.

* Monitores de sobremesa.

* Pantallas planas.

* Proyectores.

Nuevas interfaces se basan en tecnologías multimodales (entrada por voz y teclado, salida multimedia), tecnologías gestuales o tecnologías afectivas.

## Evolución de las interfaces de usuario

---

**Memex** de Vannerbar Bush (1945) describe un dispositivo para suplementar la memoria humana, para almacenar libros, grabaciones y comunicaciones. Propuso *"rastros"* para enlazar distintos elementos.

Contemplaba otras características como: reconocimiento de voz, memoria asociativa, transferencia de datos entre dispositivos, grabación de imágenes.

---

* Las primeras *"interfaces"* de usuario aparecen en la década de 1940.

* En 1962 aparece el **Sketchpad**, el primer editor gráfico interactivo.

* Desde el primer IBM PC (1981) y durante una década, la interfaz principal era la consola.

<img title="" src="https://www.winhistory.de/more/bilder/win2kdos.gif" alt="" data-align="center">

En 1973, el Xerox PARC desarrolló la computadora personal Alto, la cual tenía una pantalla de mapa de bits y fue la primera computadora en demostrar la metáfora de escritorio y la interfaz gráfica de usuario (GUI). Sin embargo, el primer producto comercial exitoso en usar una GUI fue el Macintosh de 1984:

<img src="https://s3.amazonaws.com/s3.timetoast.com/public/uploads/photo/17833656/image/medium-5a5c198cff3cf77254753407e50e0134.png" title="" alt="" data-align="center">

Los entornos gráficos en PC se popularizaron a partor de Windows 3.0 (1990):

<img src="https://i.pinimg.com/originals/a2/62/3b/a2623b325b96a5bd0f79f72fc7727726.gif" title="" alt="" data-align="center">

# 2. Análisis de Requisitos

## Objetivos

* Estudiar el Diseño Centrado en el Usuario (DCU o *Human Centered Design - HCD* por sus siglas en inglés ).

* Conocer los procesos para la recogida y especificación de requisitos.

* Estudiar distintas técnicas para recopilar información:
  
  * Sobre los usuarios.
  
  * Sobre las tareas que realizan.
  
  * Sobre el entorno donde las realizan.

## Diseño Centrado en el Usuario

Involucra a los usuarios durante el proceso de diseño y desarrollo y se centra en **entender**:

* A los usuarios.

* Tareas que realizan con el sistema.

* Entornos en los que se usará el sistema.

**¿Quiénes son los usuarios**
Son los clientes (que pagan y dan las especificaciones del sistema), otras personas en la organicazión con intereses en el desarrollo, usuarios finales (que son los que realmente interacción directamente son el sistema), etc. A todos ellos se les conoce como los interesados (***stakeholders***).

Distingue entre usuarios primarios (como el bibliotecario o el agente viajes) y usuarios secundarios (la persona que se lleva prestado un libro de la biblioteca, o que reserva un vuelo).

Los **principios **del DCU son:

* Implicación activa de los usuarios.

* Asignación apropiada de funciones entre usuario y sistema.

* La iteración de soluciones de diseño.

* Equipos de diseño multicisciplinar.

**Actividades** en el DCU:

* Entender y especificar el contexto de uso.

* Especificar los requisitos del usuario y de la organización.

* Producir soluciones (prototipos).

* Evaluar diseños con los usuarios a partir de los requisitos.

El ciclo de vida se representa por el siguiente grafo en forma de estrella:

<img src="https://www.researchgate.net/profile/Marcelo-Guimaraes/publication/326052219/figure/fig1/AS:651334961352705@1532301764869/The-Star-Life-Cycle-4.png" title="" alt="" data-align="center">

**¿Cuándo y cómo implicar a los usuarios?**

* Pronto: durante las especificaciones de requisitos.

* Durante el prototipado, para probar diseños y opciones.

* Justo antes de publicar el sistema.

* Durante la formación, después de publicar el sistema.

Cuánto más tarde en el proceso, menos cambios se podrán realizar.

## Análisis de Requisitos

El **Requisito** es una declaración sobre un futuro producto que especifica qué debería hacer o cómo debería comportarse.

* Los requisitos se pueden definir con distintos niveles de abstracción.

* Normalmente se obtienen mediante observación, entrevistas o encuentas.

* Describen lo que debería hacer el sistema, y no cómo.

Una especificación sería: *"El usuario deberá poder obtener la factura de su compla. La factura estará disponible en formato PDF"*.

Se especifican **dos tipos de Requisitos:**

* **Funcionales:** qué debería hacer el sistema.
  
  * *"El procesador de texto debería permitir establecer el formato a nivel de documento, página, palabra y letra."*

* **No funcionales:** restricciones sobre el sistema y su desarrollo.
  
  * *"Debería poder ejecutarse en Windows, Mac y Linux."*
  
  * *"El desarrollo del sistema debería durar menos de 6 meses."*

La **Especificación de Requisitos Software** es el restulrado de la fase de análisis de requisitos. Es un documento que recoge todos los requisitos de una forma estructurada. Existen distintos **estándares**:

* IEEE 29148-2011 -  Systems and software engineering - Life cycle processes - Requirements engineering. 2011.

* Volere.

### Análisis de Requisitos: Recogiendo información

#### Estudios **etnográficos**

* Observar a los usuarios mientras hacen trabajo real en su lugar de trabajo, o usando un sistema en sus hogares.

* Saber qué hacen los usuarios, pero también qué les gusta o no.

**Tipos de observación:**

* **Observación directa:**
  
  * **Estudios de campo:** el observador toma notas sobre comportamientos interesantes en el lugar de trabajo/hogar.
  
  * **Estudios controlados:** el usuario interacciona con el sistema en un entorno controlado (normalmente un laboratorio de usabilidad).
  
  * **Ventajas:** fácil, genera resultados interesantes.
  
  * **Desventajas:** sólo una oportunidad para capturar la información, difícil anotar todos los aspectos de la actividad, lo que no se anota, se pierde, es intrusivo y puede alterar el comportamiento y el rendimiento de los usuarios.

* **Observación indirecta:**
  
  * Grabar en video, caputa de pulsaciones de teclado/ratón, etc.
  
  * **Ventajas:** se captura toda la interacción, más objetivo.
  
  * **Desventajas:** el análisis de datos es costoso, algunos usuarios pueden sentirse intimidados.

#### Estudios de usuarios

Diseñar una interfaz de usuario para un tipo de usuario es fácil. Diseñar una IU para diferentes niveles de experiencia (multi-capa) es complicado.

* Proporcionar a los usuarios noveles una interfaz simplificada y reducida.

* Dependiendo de la progresión del usuario, añadir herramientas de mayor nivel para realizar tareas más complejas.

* Aplicar el diseño multi-capa a la ayuda on-line, mensajes de error y tutoriales.

* Idealmente permitir al usuario configurar el entorno: contenido de los menús, nivel de realimentación, densidad de la información, o ritmo de interacción.

#### Ánalisis de la competencia

Un análisis competitivo es un camino fácil y rápido para establecer un punto de partida en el diseño.

* Actividades.

* Revisar las versiones previas de la aplicación y compararlas con las de la competencia.

* Desde el punto de vista de la usabilidad, buscaremos buenas ideas de interfaz de usuario para aplicarlas a nuestro diseño.

#### Análisis de Tareas

Despues de identificar a los usuarios, debemos entender los objetivos que tienen al usar el sistema.

El análisis de tareas es una actividad que estudia qué debe hacer un sistema y la funcionalidad que debe ofrecer a los usuarios para que alcancen sus objetivos.

Terminología:

* **Objetivo:** resultado final a obtener.

* **Tarea:** conunto estructurado de actividades realizadas en algún orden.

* **Acción:** operación o paso individual de una tarea.
