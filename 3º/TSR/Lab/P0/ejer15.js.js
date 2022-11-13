function fuera(x,y) {
    return (z) => { return x[y](z+0)}
}

var v = [
    (a)=> {return a+1}, 
    (a)=> {return a+3},
    (a)=> {return a+2}
]

let w = fuera(v,1)

console.log(w(v[2]("cero")))
console.log(w(v[0](1)))