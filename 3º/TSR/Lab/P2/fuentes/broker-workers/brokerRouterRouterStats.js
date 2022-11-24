const {zmq, lineaOrdenes, traza, error, adios, creaPuntoConexion} = require('../tsr')
lineaOrdenes("frontendPort backendPort")
let workers  =[] // workers disponibles
let pendiente=[] // peticiones no enviadas a ningun worker
let enviadas =[]
let frontend = zmq.socket('router')
let backend  = zmq.socket('router')
creaPuntoConexion(frontend, frontendPort)
creaPuntoConexion(backend,  backendPort)

function procesaPeticion(cliente,sep,msg) { // llega peticion desde cliente
	//traza('procesaPeticion','cliente sep msg',[cliente,sep,msg])
	if (workers.length)
		backend.send([workers.shift(),'',cliente,'',msg])
		
	else pendiente.push([cliente,msg])
}
function procesaMsgWorker(worker,sep1,cliente,sep2,resp) {
	//traza('procesaMsgWorker','worker sep1 cliente sep2 resp',[worker,sep1,cliente,sep2,resp])
	console.log("\x1b[34mWorker " + worker + " añadido a lista de workers disponibles\x1b[0m")
	if (enviadas[worker] == null || enviadas[worker] == undefined)
		enviadas[worker] = 0
	else
		enviadas[worker]++

	if (pendiente.length) { // hay trabajos pendientes. Le pasamos el mas antiguo al worker
		let [c,m] = pendiente.shift()
		backend.send([worker,'',c,'',m])
	}
	else workers.push(worker) // añadimos al worker como disponible
	if (cliente) frontend.send([cliente,'',resp]) // habia un cliente esperando esa respuesta
}

frontend.on('message', procesaPeticion)
frontend.on('error'  , (msg) => {error(`${msg}`)})
 backend.on('message', procesaMsgWorker)
 backend.on('error'  , (msg) => {error(`${msg}`)})
 process.on('SIGINT' , adios([frontend, backend],"abortado con CTRL-C"))

 setInterval(function () {
	console.log("\x1b[33m\x1b[1m---Estadísticas---\x1b[0m")
	if (workers.length == 0) console.log("\x1b[31mSin workers por ahora\x1b[0m")
	else
		workers.forEach((worker) => console.log("-\x1b[33mWorker \x1b[1m" + worker + "\x1b[0m\x1b[33m con \x1b[97m" + enviadas[worker] + "\x1b[33m mensajes procesados.\x1b[0m"))
 }, 5000)
