const net = require('net');

if (process.argv.length < 4) {
	console.log('Incorrect use: node netClientLoad.js IP_server IP_local')
	return
}

let args = process.argv.slice(2)
let IP_servidor = args[0]
let IP_local = args[1]

const client = net.connect({port:8000, address: IP_servidor}, function() { //connect listener
	console.log('client connected');
	client.write('Client: Give me my load please!\r\n');
});

client.on('data', function(data) {
 	console.log(data.toString());
 	client.end(); //no more data written to the stream
});

client.on('end', function() {
	console.log('client disconnected');
});
