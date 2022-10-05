'use strict';	// With strict mode, you can not, for example, use undeclared variables

console.log ("hola mundo")

let cnt = 0;
function imprime (msg) {
	console.log (cnt++ + ".- " + msg);
}

imprime ("hola mundo")
imprime ("adios")
