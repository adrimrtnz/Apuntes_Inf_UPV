// callback síncrono
function suma(a, b, cb) {
    let result = a + b;
    cb(result);
}


suma(2,3, (res) => {
        console.log("Resultado: " + res)
})