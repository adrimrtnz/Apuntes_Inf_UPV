//let gl1=0          // 0

function a() {
    let a1=1
    b(a1)
}

function b(p1) {
    let b1=2
    //console.log(a1) // Error
    console.log(b1)
    //console.log(p1)
    console.log(gl1)
}

var gl1=0               // 0
a()
// let gl1=0           // Error, con 'let' visible desde este punto en adelante
//var gl1=0              // undefined