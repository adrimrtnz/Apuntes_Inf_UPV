La **jerarquía de Chomsky** es un marco de estudio de los lenguajes formales basado en una taxonomía de las gramáticas en función de la forma que toman las producciones. Se proponen cuatro grandes familias de gramáticas que, a su vez, definen cuatro familias de lenguajes:
+ **Gramáticas de tipo 0 o no restringidas**: No tienen ningún tipo de restricción.
+ **Gramáticas de tipo 1 o sensibles al contexto**: 
	+ Las producciones toman la forman: $\alpha A \beta \rightarrow \alpha \gamma \beta \quad \alpha,\beta \in (N \cup T)^*, A\in N,\gamma \in (N\cup T)^+$
	+ Adicionalmente se permite la regla $S \rightarrow \lambda$ siempre que $S$ no aparezca como consecuente en ninguna producción.
+ **Gramáticas de tipo 2 o de contexto libre o incontextuales**:
	+ Las producciones toman la forma: $A\rightarrow \alpha \quad \alpha \in(N\cup T)^*,A\in N$
+ **Gramáticas de tipo 3 o regulares** que se subdividen en dos tipos:
	+ Gramáticas lineales por la derecha.
	+ Gramáticas lineales por la izquierda.

Desde el punto de vista de las clases de lenguajes, los cuatro tipos de gramáticas definidas en la jerarquía de Chomsky definen cuatro familias de lenguajes, atendiendo al siguiente criterio:
> *"Un lenguaje es de tipo $i$ si existe una gramática de tipo $i$ que lo genera"*

De esta forma y desde el punto de vista de las clases de lenguajes que origina los cuatro tipos de gramáticas, la **jerarquía de Chomsky** establece una relación de clases de lenguajes que obecede al siguiente esquema:

![diagrama_jerarquia](http://blogs.elpais.com/.a/6a00d8341bfb1653ef017d3d9abfd1970c-pi)