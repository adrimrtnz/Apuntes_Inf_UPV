Ampliaciones:

- Mejora de la interfaz:
	- Alabeo: Con las teclas Q y W se puede alabear la nave a izquierda y derecha respectivamente.
	- Disparo: Con el botón izquierdo del ratón se puede generar un disparo. La aplicación genera 5 balas
	           al inicio que se van disparando en array circular.
	- Sonidos: Se han añadido sonidos de disparo, de explosión y de colisión (al pasar por misma posición que un meteorito).

- Mejora de la geometria:
	- Ahorro de geometría visible: No se dibujan aquellos meteoritos que están detrás del punto de
		 vista de la nave (función bool esta_detras(Vec3 poi, Vec3 pos) en utils.h)
	- Primitivas propias: se define el dibujado del cubemap de la nave, cubemap fondo y dibujado de las alas.
			    Además de la inclusión del piloto en la vista en tercera persona.
	- Cada meteorito tiene una instancia diferente en su configuración de stacks y slices.

- Mejora de apariencia:
	- Fondo estelar: cubemap con textura propia que sigue la posición de la nave para ser inalcanzable.
	- Texturas: Diferentes para las alas de la nave, interior de la nave, exterior de la nave, piloto y sol.
	- GUI: Arriba a la izquierda se ha colocado información de la velocidad, meteoritos destruidos e indicador de encendido de luces.

- Mejora de la animacion:
	- Explosiones: cuando un disparo impacta en un meteorito se genera una explosión allá donde
		estaba el meteorito.
	- Los meteoritos tienen su propio vector de movimiento independiente, y una vez destruidos se reutiliza
	 	esta geometría teletransportandolo a algún otro luegar del espacio dentro de unos márgenes.

- Mejoras en las vista:
	- Camara en primera persona: Se puede mover la cabeza del piloto con las teclas derecha e izquierda.
				Con la tecla de dirección hacia delante se resetea el ángulo de visión.
	- Camara en tercera persona: con la tecla P se activa la vista en tercera persona. Con la misma
		relación de flechas anterior, se puede ver alrededor de la nave y si estamos viendo la parte
		delantera de esta, podemos ver al piloto.
		Para esta vista se han tenido que tener en cuenta el orde de dibujado de las caras de la nave
		para que se vieran las traseras si se tenían que ver a través de las transparencias.
		En esta vista, la nave acompaña las rotaciones de la dirección.
	- Minimapa: al pulsar la tecla TAB se muestra/oculta un minimapa en la parte superior derecha que muestra
		la posición relativa de la base así como la diferencia de altura entre la nave y la base.


- SOBRE LOS SONIDOS: Para facilitar el port del proyecto se han utilizado librerias básicas que creo según vi
	deberían estar presentes en todas las máquinas Windows. Si hubiera algún problema con los sonidos, al
	inicio del Main.cpp existe una macro #define SOUND_ON que si se cambia o elimina, todo el código de los
	sonidos no se tiene en cuenta.

- SOBRE EL CÓDIGO: A parte del Main.cpp hay 4 archivos más:
	- Meteorito.h : Clase que modela el comportamiento de los meteoritos.
	- Bala.h : Clase que modela el comportamiento de las balas de la nave.
	- config.h : Mayoría de constantes y definiciones de arrays de colores, cubemaps, etc.
	- utils.h : algunas funciones de dibujado o de alguna utilidad (puestas aquí para limpiar un poco el Main.cpp)
	- carpeta img : carpeta de imagenes y texturas, colocada en la raiz del proyecto.
	- carpeta sound : carpeta de archivos de sonido, colocada en la raiz del proyecto.