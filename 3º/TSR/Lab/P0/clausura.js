
function creaFunc() {
    let nombre = "Mozilla"
    return () => { console.log(nombre) }
}

function multiplicarPor(x) {
    return y => { return x*y }
}

let tables=[]
for (let i=1; i<=10; i++)
    tables[i]=x=>i*x

console.log(tables[5](2))
console.log(tables[9](2))


let miFunc = creaFunc()
miFunc()

let triplicar = multiplicarPor(3)
y = triplicar(21)
console.log("y = " + y)

/* ---------------------------------------------------- */
function writing(x) {
    console.log("---\nWriting after " + x + " seconds")
}

function writingClosure(x) {
    return () => {
        console.log("---\nWriting after " + x + " seconds")
    }
}

setTimeout(() => { return writing(6) }, 6000) // OR setTimeout( function() {writing(6)}, 6000)
setTimeout(writing, 3000)
setTimeout(writingClosure(4), 4000)
console.log("root(2) = " + Math.sqrt(2))

function imprimeEn(x) {
    return setTimeout(() => {writing(x)}, x * 1000)
}

imprimeEn(5)