const net = require('net');
const LOCAL_PORT = 50921;
const LOCAL_IP = '127.0.0.1';
//
//const REMOTE_IP="cdt.gva.es";
//const REMOTE_IP="apache.rediris.es"
//const REMOTE_IP="sepie.es"
//const REMOTE_IP = '158.42.4.23'; // www.upv.es

let args = process.argv.slice(2)
let REMOTE_IP = args[0]
let REMOTE_PORT = args[1]
const PROG_PORT = 50922

const server = net.createServer(function (socket) {
 const serviceSocket = new net.Socket();
 serviceSocket.connect(parseInt(REMOTE_PORT), REMOTE_IP, function () {
 	socket.on('data', function (msg) {
 	console.log (msg + "")
 	serviceSocket.write(msg);
 });
 	serviceSocket.on('data', function (data) {
 		socket.write(data);
 	});
});
}).listen(LOCAL_PORT, LOCAL_IP);
console.log("TCP server accepting connection on port: http://" + LOCAL_IP + ":" +
LOCAL_PORT);

const programador = net.createServer( function(c) { //connection listener
	console.log('server: client connected');
 	c.on('end', function() {
		console.log('server: client disconnected');
 	});
 
 	c.on('data', function(data) {
		console.log("---DATOS RECIBIDOS POR EL PROGRAMADOR---")
		console.log("MSG: " + data);

		let newData = JSON.parse(data)
		const NEW_REMOTE_IP = newData.remote_ip;
		const NEW_REMOTE_PORT = newData.remote_port;

		console.log("NEWDATA:" + newData);
		console.log("NEW_REMOTE_IP: " + NEW_REMOTE_IP)
		console.log("NEW_REMOTE_PORT: " + NEW_REMOTE_PORT)

		REMOTE_IP = NEW_REMOTE_IP
		REMOTE_PORT = NEW_REMOTE_PORT

		c.write('Proxy received:\r\n\t'+ data.toString()); // send resp
 		//c.write(getLoad().toString())
		c.end(); // close socket
 	});
});

programador.listen(PROG_PORT, '127.0.0.1', function() { //listening listener
	console.log('programer bound');
});

