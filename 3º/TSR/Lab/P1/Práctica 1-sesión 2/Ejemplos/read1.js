const fs = require('fs');
fs.readFile('/etc/hosts', 'utf8', function (err,data) {
 	if (err) {
 		return console.log(err);
 	}
 	console.log(data);
});


function readFilePromise(filename) {
	return new Promise( (resolve, reject) => {
		fs.readFile(filename, (err, data) => {
			if (err) reject(err + '')
			else resolve(data + '')
		})
	})
}

async function readTwoFile() {
	try {
		console.log(await readFilePromise("read1.js"))
		console.log(await readFilePromise("doesntExist.js"))
	} catch (err) {
		console.log(err + '')
	}
}

readFilePromise('read1.js').then(console.log, console.error)
readFilePromise('/etc/hoteles').then(console.log, console.error) // archivo que no existe

readTwoFile()