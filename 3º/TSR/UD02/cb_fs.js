const fs = require('fs');

fs.readFile('cb_fs.js', function(err, buffer) {
    if (err) {
        // Handle error
        console.error(err.stack);
        return;
    }
    // Do something
    console.log(buffer.toString());
});

console.log('Ejecutando otras instrucciones');
console.log('raiz(3)=', Math.sqrt(3));