const ev = require('events')
const { emit } = require('process')
const emitter = new ev.EventEmitter

const e1 = "uno"
const e2 = "dos"
const e3 = "tres"


let e2_time = 2000
let interval_e2

function listener1() {
    c.increment_e1();
    console.log("Evento uno.");
}

function listener2() {
    c.increment_e2();
    
    if (c.get_e2() >= c.get_e1()) {
        console.log("Evento dos.")
    }
    else
    console.log("Hay más eventos del tipo 'uno'")
}

function listener3() {
    console.log("Evento tres.");
    
    if (e2_time < 18000) {
        clearInterval(interval_e2)
        e2_time *= 3
        interval_e2 = setInterval(function() {emitter.emit(e2)}, e2_time)
    }
}


function counter() {
    let n_e1 = 0
    let n_e2 = 0
    
    return {
        increment_e1() {n_e1++},
        increment_e2() {n_e2++},
        get_e1() {return n_e1},
        get_e2() {return n_e2} 
    }
}

// TODO: hacerlo con función generadora
let c = counter()
emitter.on(e1, listener1)
emitter.on(e2, listener2)
emitter.on(e3, listener3)

setInterval(function() {emitter.emit(e1)}, 3000)
setInterval(function() {emitter.emit(e3)}, 10000)
interval_e2 = setInterval(function() {emitter.emit(e2)}, e2_time)