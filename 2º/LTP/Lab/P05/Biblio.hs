module Biblio where

    type Person = String
    type Book = String
    type Database = [(Person, Book)]

    exampleBase :: Database
    exampleBase = [
        ("Alicia", "El nombre de la rosa"),
        ("Juan", "La hija del canibal"),
        ("Pepe", "Odesa"),
        ("Alicia", "La ciudad de las bestias")]

    obtain :: Database -> Person -> [Book]
    obtain dBase thisPerson 
        = [book | (person,book) <- dBase, person == thisPerson]
    
    borrow :: Database -> Book -> Person -> Database
    borrow dBase book person = dBase ++ [(person, book)]

    return' :: Database -> (Person,Book) -> Database
    return' dBase pbTupla 
        = [ chckTupla | chckTupla<-dBase, chckTupla /= pbTupla]