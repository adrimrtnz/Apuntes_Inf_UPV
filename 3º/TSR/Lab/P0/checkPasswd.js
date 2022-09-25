function doCheckPasswd(input, correctPassword, func) {
    if (input === correctPassword) {
        func()
    }
}

doCheckPasswd("Erroneous", "Correct", () => console.log("access granted"))

doCheckPasswd("Correct", "Correct", () => console.log("sending data"))