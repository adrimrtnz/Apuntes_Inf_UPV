# Seminario 1: Lenguaje C
Se ha explicado los conceptos básicos de C. Hay una "chuleta" en poliformat con las principales funciones estándar de C.

C es un lenguaje basado en funciones.
* Siempre tiene que haber una **función** `main()`.
* Definición de una función en C:

```C
tipo_retorno nombre_funcion(tipo1 arg1, ..., tipoN argN) {
    [declaración de variables locales;]
    codigo ejecutable
    [return expresión;]
}
```

Para editar código estamos usando `kate [nombre del programa]&`, en este caso usando el editor *kate*. El `&` al final del comando hace que el **shell** no espere hasta el fin del comando.