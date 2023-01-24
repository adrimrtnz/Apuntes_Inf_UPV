const os = require('os')

process.stdout.write("Radius of the circle: ")
process.stdin.resume()
process.stdin.setEncoding('utf8')

process.stdin.on('data', function (str) {
    let rd = str.slice(0, str.length - os.EOL.length)
    console.log('Circunference for radius ' + rd + ' is ' + (2 * rd * Math.PI))
    console.log(' ')
    process.stdout.write('Radius of the circle: ')
})

process.stdin.on('end', function() {console.log('Finishing...')})