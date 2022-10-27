const ev = require('events')
const emitter = new ev.EventEmitter()
const e1 = 'print', e2 = 'read'

function createListener(eventName) {
    let num = 0
    return function() {
        console.log('Event ', eventName, ' has ',
        'happenned ' + ++num, ' times')
    }
}

emitter.on(e1, createListener(e1))
emitter.on(e2, createListener(e2))

emitter.on(e1, () => {
    console.log('Something has benn printed!')
})

setInterval(() => {emitter.emit(e1)}, 2000)
setInterval(() => {emitter.emit(e2)}, 3000)