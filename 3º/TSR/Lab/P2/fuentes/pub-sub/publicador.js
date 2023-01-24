const {zmq, error, lineaOrdenes, traza, adios, creaPuntoConexion} = require('../tsr')
lineaOrdenes("port numMensajes tema1 tema2 tema3")
let temas = [tema1,tema2,tema3]

var pub = zmq.socket('pub')
creaPuntoConexion(pub, port)

function envia(tema, numMensaje, ronda) {
	traza('envia','tema numMensaje ronda',[tema, numMensaje, ronda])
	pub.send([tema, numMensaje, ronda]) 
}
function publica(i) {
	return () => {
		envia(temas[i%3], i, Math.trunc(i/3))
		if (i==numMensajes) adios([pub],"No me queda nada que publicar. Adios")()
		else setTimeout(publica(i+1),1000)
	}
}
setTimeout(publica(0), 1000)

pub.on('error', (msg) => {error(`${msg}`)})
process.on('SIGINT', adios([pub],"abortado con CTRL-C"))