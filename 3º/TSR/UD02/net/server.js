const net = require('net')

let server = net.createServer(
    function(c) { // 'connection' listener
        console.log('Server: Client connected')

        c.on('end', function() {
            console.log('Server: Client disconected')
        })

        c.on('error', function() {
            console.log('Server: some connection error')
        })

        c.on('data', function(data) {
            console.log('Server: data from client -> ' +
            data.toString())
            c.write(data)
        })
    }
)

server.listen(9000, function () {
    console.log('Server bound')
})