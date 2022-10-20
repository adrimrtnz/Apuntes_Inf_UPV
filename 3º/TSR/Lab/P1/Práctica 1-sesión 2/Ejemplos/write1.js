const fs = require('fs');
fs.writeFile('/tmp/f', 'contenido del nuevo fichero\n', 'utf8', function (err) {
	if (err) {
 		return console.log(err);
 	}
 	console.log('se ha completado la escritura');
});
