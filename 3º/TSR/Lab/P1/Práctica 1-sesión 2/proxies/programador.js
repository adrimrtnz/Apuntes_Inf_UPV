const net = require('net');

let args = process.argv.slice(2)
const NEW_IP = args[0]
const NEW_PORT = args[1]
const PROXY_PORT = 50922

const client = net.connect({port:PROXY_PORT, address: '127.0.0.1'}, function() { //connect listener
	console.log('programmer connected');
    var msg = JSON.stringify({'remote_ip' : NEW_IP, 'remote_port' : NEW_PORT})
	client.write(msg + '\r\n');
});

client.on('data', function(data) {
 	console.log(data.toString());
 	client.end(); //no more data written to the stream
});

client.on('end', function() {
	console.log('client disconnected');
});
