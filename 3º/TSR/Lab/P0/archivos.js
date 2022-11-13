const fs = require('fs')

function afterReading(n) {
    return function(err, data) {
        if (err) console.error(n, 'not found')
        else console.log(data.toString())
    }
}

for (var i = 1; i <= 2; i++) {
    fs.writeFileSync('data' + i + '.txt', 'Hello ' + i)
}
for (var i = 1; i <= 3; i++) {
    var name = 'data' + i + '.txt'
    var time = 100 - 10 * i

    setTimeout(function() {
        fs.readFile(name, afterReading(name))
    }, time)
}

console.log("root(" + i + ") =", Math.sqrt(i))