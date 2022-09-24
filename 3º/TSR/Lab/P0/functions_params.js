function add(x, y, z) {
    return x + y + z
}

console.log(add(1,2,3))     // 1+2+3
console.log(add(2,7))       // NaN
console.log(add(null))      // NaN
console.log(add(1,2,3,4,5)) // 1+2+3


/* ============================================ */
/* ===          DEFAULT PARAMS              === */
/* ============================================ */
function add_v2(x=0, y=0, z=0) {
    return x + y + z
}

console.log(add_v2(1,2,3))     // 1+2+3
console.log(add_v2(2,7))       // 2+7+0
console.log(add_v2(null))      // 0+0+0
console.log(add_v2(1,2,3,4,5)) // 1+2+3