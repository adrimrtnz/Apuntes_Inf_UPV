const net = require('net')
let cont = 0

let client = net.connect({port: 9000},
    function() {
        console.log('Client: connected')

        client.write(cont + ' world!')
    })

client.on('data', function(data) {
    console.log(data.toString())
    
    if (cont > 1000) client.end()
    else client.write((++cont) + ' world!')
})

client.on('end', function() {
    console.log('Client: disconnected')
})

client.on('error', function() {
    console.log('Client: some connection error')
})