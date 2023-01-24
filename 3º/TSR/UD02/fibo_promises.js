function fibo(n) {
    return (n<2) ? 1 : fibo(n-2) + fibo(n-1);
}

function fibo_promise(n) {
    return new Promise(function(fulfill, reject) {
        if (typeof(n) != 'number')
            reject(n+ ' is an incorrect argument');
        else
            setTimeout(function() {
                fulfill(fibo(n))} ,1)
    })
}

function onSuccess(i) {
    return function (res) {
        console.log('fibonacci(' + i + ') = ', res);
    }
}

function onError(err) {
    console.log('Error: ', err);
}


console.log('Execution is starting...');
let elems = [25, '5', true]

for (let i in elems)
    fibo_promise(elems[i])          // elems[i]).then( onSuccess(elems[i]), onError)
        .then(onSuccess(elems[i]))
        .catch(onError);