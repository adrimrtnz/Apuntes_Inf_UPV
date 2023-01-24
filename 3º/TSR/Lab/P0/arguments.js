function changeColor(car, newColor) {
    return car.color = newColor
}

function changeCar(car) {
    car = {
        brand: 'Ferrari',
        color: 'Red'
    }
}

let myCar = {
    brand: 'Volvo',
    color: 'Grey'
}

console.log(changeColor(myCar, 'Blue'))
changeCar(myCar)
console.log(myCar)

console.log(JSON.stringify(myCar))