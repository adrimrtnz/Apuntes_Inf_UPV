function fibo(n) {
    return (n<2) ? 1 : fibo(n-2) + fibo(n-1);
}

function fibo_async(n, cb) {
    process.nextTick(function() {
        let err = eval_err(n, 'fibonacci');
        let m = err ? '' : fibo(n);
        cb(err, 'fibonacci(' + n + ') = ' + m)
    });
}

function fact(n) {
    return (n<2) ? 1 : n * fact(n-1);
}

function fact_async(n, cb) {
    process.nextTick(function() {
        let err = eval_err(n, 'factorial');
        let m = err ? '' : fact(n);
        cb(err, 'factorial(' + n + ') = ' + m)
    });
}

function show_back(err, res) {
    if (err) 
        console.log(err)
    else
        console.log(res)
}

function eval_err(n,s) {
    return (typeof n != 'number') ?
        s + '(' + n + ') ??? :' + n + ' is not a number' : '';
}


console.log('Iniciando ejecución...');

fact_async(10, show_back);
fact_async('ana', show_back);
console.log('lanzados cálculos factorial...');

fibo_async(40, show_back);
fibo_async('pep', show_back);
console.log('lanzados cálculos fibonacci...');