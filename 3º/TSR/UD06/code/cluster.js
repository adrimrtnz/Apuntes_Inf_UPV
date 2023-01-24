let cluster = require('cluster')
let http = require('http');

let numCPUs = require('os').cpus().length;
let server = '127.0.0.1';
let port = parseInt(process.argv[2]) || 8000;
let reqs = {};

if(cluster.isMaster) {
    let numReqs = 0;
    setInterval(() => { console.log("numReqs = ", numReqs); }, 1000);
    function messageHandler(msg) {
        if (msg.cmd && msg.cmd == 'notify') numReqs++
    }

    for (let i=0; i < numCPUs; i++) {
        cluster.fork();
    }
    for (let worker in cluster.workers) {
        console.log("Configuring worker: ", worker);
        cluster.workers[worker].on('message', msg => { 
            console.log("Message from worker: ", worker);
            reqs[worker] = reqs[worker] ? reqs[worker]+1 : 1;
            messageHandler(msg) 
        });
    }

    cluster.on('exit', function(worker, code, signal) {
        console.log('server', worker.process.pid, 'died');
    });

} else {
    server = http.createServer(
        function (request, response){
        response.writeHead(200, {'Content-type': 'text/plain'});
        process.send({ cmd: 'notify'});
        response.end('Hello World!');
       });    
    server.listen(port);
}


