a. Obtener el DNI y el nobre de los profesores que imparten todas las asigntauras del departamento DSIC.

```sql
SELECT P.dni, P.nombre
FROM Profesor P
WHERE NOT EXIST (
			   SELECT *
			   FROM Asignatura A
			   WHERE cod_dep = 'DSIC'
			   AND NOT EXIST (SELECT * FROM Docencia D
					    WHERE P.dni = D.dni AND D.cod_asg = A.cod_asg)
			 )

```

Un Profesor P:
* F: Asignaturas distintas de un mismo departamento (DSIC)
* G: Profesor P imparte esa asignatura (Hace falta la tabla Docencia)

---

b. Obtener el código y el nobre de las **asignaturas impartidas** por todos los profesores de más de 40 años

```sql
SELECT A.cod_asg A.nombre
FROM Asignatura A
WHERE NOT EXIST (
    SELECT *
    FROM Profesor P
    WHERE P.edad > 40 AND NOT EXIST (
        SELECT * 
        FROM Docencia D
        WHERE P.dni = D.dni AND D.cod_asg = A.cod_asg
    )
    AND EXIST (SELECT * FROM Profesor P1 WHERE P1.edad > 40) -- Esto es para asegurar
)
```

* F: Profesores > 40 años
* G: Con docencia

---

c. Obtener el código y el nombre de las asignaturas impartidas **sólo** por profesores de más de 40 años.
* Ese **solo** está ocultando un **para todo**.
* F: Para todo profesor que imparte esa asignatura
* G: Tiene más de 40 años

```sql
SELECT A.cod_asg A.nombre
FROM Asignatura A
WHERE NOT EXIST (
    SELECT *
    FROM Profesor P, Docencia D
    WHERE D.dni = P.dni AND D.cod_asg=A.cod_asg AND NOT P.edad > 40

    AND EXIST (SELECT * FROM Docencia D1 WHERE D1.cod_asg=A.cod_asg) -- Esto es para asegurar
)
```