function population() {
    const pops =  [1365590000, 1246670000, 318389000];
    const names = ['China', 'India', 'USA'];
    const placeholders = ['1st', '2nd' ,'3rd', '4th'];

    let array = [];

    for (i = 0; i < pops.length; i++) {
        array[i] = function(x) {
            return function() {
                console.log("The " + placeholders[x] + " most populated country is "
                + names[x] + " and its population is " + pops[x]);
            }
        }(i);
    } return array;
}

let ps = population();

first = ps[0];
second = ps[1];
third = ps[2];

first();
second();
third();


/**
 * Alternative with ECMAScript6
 * 
function population() {
    const pops =  [1365590000, 1246670000, 318389000];
    const names = ['China', 'India', 'USA'];
    const placeholders = ['1st', '2nd' ,'3rd', '4th'];

    let array = [];

    for (let i = 0; i < pops.length; i++) {
        array[i] = function(x) {
            return function() {
                console.log("The " + placeholders[x] + " most populated country is "
                + names[x] + " and its population is " + pops[x]);
            }
        };
    } return array;
}
 */