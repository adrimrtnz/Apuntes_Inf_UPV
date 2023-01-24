const http = require('http')
const hostname = '127.0.0.1'
const port = 8080

const server = http.createServer((req, res) => {
    // res = ServerResponse
    // setHeader() sets the response header
    res.statusCode = 200
    res.setHeader('Content-Type', 'text/plain')

    res.end('Hello Web\n')
})

server.listen(port, hostname, () => {
    console.log('Server running at http://' 
    + hostname + ':' + port + '/')
})