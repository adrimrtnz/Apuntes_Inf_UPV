# Unidad didáctica 1: Bases de datos relacionales

Los **sistemas de gestión de bases de datos (SGBD)** son la tecnología informática actual para la gestión de grandes volúmenes de datos estructurados en memoria secundaria.

## Sistemas de la información
Un **sistema de Información** es un conjunto de elementos ordenadamente relacionados entre sí de acuerdo a ciertas reglas que aportan a la organización a la que sirven la información necesaria para el cumplimiento de sus fines.

Sus partes:
* Contenido.
* Equipo físico.
* Equipo Lógico.
* Administrador.
* Usuarios.

Sus funciones:
* Recogida (de datos).
* Almacenamiento.
* Procesamiento.
* Recuperación.

## Bases de datos
Una Base de Datos (BD) es una colección estructurada de datos que tiene:

**Propiedades estáticas**:
* Objetos.
* Relaciones entre objetos.
* Restricciones.

**Propiedades dinámicas**:
* Sucesos.
* Restricciones.

Los mecanismos de estructuración de datos (estructuras de datos) que se pueden utilizar dependen del **sistema informático** con el que se vaya a crear y manipular la base de datos $\rightarrow$ SGBD.

Los **SGBD** son herramientas (software) para la gestión (creación y manipulación) de bases de datos.

## Características de las técnicas de bases de datos
La tecnología de bases de datos ha **evolucionado** intentando dar resputesta a las crecientes **exigencias** de funcionalidad y eficiencia que los usuarios platean a los sistemas de información.

### Características
* **Integración** de toda la información de la organización.
* **Persistencia** de los datos.
* Accesibilidad simultánea para distintos usuarios.
* Descripción unificada de los datos e independiente de los programas.
* **Independencia** de los **programas** respecto a la representación física de los datos.
* Definición de **vistas** parciales de los datos para distintos usuarios.
* Mecanismos para controlar la **integridad** y la **seguridad** de los datos.

---

## Modelo Relacional de datos
* Propuesto por E.F. Codd en 1970.
* Se immpuso a los modelos anteriores (jerárquico y red) durante la década de los ochenta.
* Es el modelo dominante hasta la actualidad (2022) debido a su sencillez.

## Definición informal de una Base de Datos Relacional (BDR)
En una base de datos relacional la información se estructura en *tablas* organizadas en **filas** y **columnas**.
* Las **filas** de una tabla tienen una estructura semejante y almacenan información similar de distintos objetos o individuos del mundo real.
* Cada **columna** almacena una determinada propiedad de esos objetos. Los valores que pueden aparecer en una columna han de ser todos del mismo **tipo de datos**.