function square(x) { return x*x }

let a = square
let b = a(3)
let c = a

console.log(a)      // [Function: square]
console.log(b)      // 9
console.log(c)      // [Function: square]


/*
function product(a,b) {
    return a*b
}

function add(a,b) {
    return a+b
}

function substract(a,b) {
    return a-b
}
*/

// let arithmeticOperations = [product, add, substract]

let arithmeticOperations = [        // Anonymous definition
    function(a,b) {return a*b},
    function(a,b) {return a+b},
    function(a,b) {return a-b}
]

console.log(arithmeticOperations[1](2,3))   // add(2,3)

function doWithNFirstNumber(n, op, op2) {
    result = op(1)

    for (let c=2; c <= n; c++) {
        aux = op(c)
        result = op2(result, aux)
    }

    return result
}

// Sum the squares of the first four numbers. Result: 30
console.log(doWithNFirstNumber(4, x => x*x, arithmeticOperations[1]))

// Compute how many odd numbers are in the 1..3 range. Result: 2
console.log(doWithNFirstNumber(3, x => x%2 ? 1:0, arithmeticOperations[1]))