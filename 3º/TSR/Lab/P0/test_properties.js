function printDistrict(who) {
    console.log("District: " + who.district)
}

let person = {
    name: "Peter",
    age: 25,
    address: {
        city: "Valencia",
        street: "Tres Cruces",
        number: 12
    }
}

printDistrict(person)      // District: undefined

for (let property in person)
    console.log("Property " + property + ": " + person[property])