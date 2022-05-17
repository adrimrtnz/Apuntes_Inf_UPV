
-- devuelve los primeros valores de la lista hasta
-- que la suma de los mismos sea >= n
primerosSuma :: Int -> [Int] -> [Int]
primerosSuma _ [] = []
primerosSuma n (x:xs)
        | n > x = x : primerosSuma (n-x) xs
        | otherwise = [x]

-- definir la funcion "==" para el tipo Stack a
data Stack a        = EmptyStack | Stk a (Stack a) deriving Show 
empty :: Stack a
push :: a -> Stack a -> Stack a
top :: Stack a -> a
pop :: Stack a -> Stack a
isEmpty :: Stack a -> Bool

push x s            = Stk x s
top (Stk x s)       = x
pop (Stk _ s)       = s
empty               = EmptyStack
isEmpty EmptyStack  = True 
isEmpty (Stk x s)   = False

length' :: Stack a -> Int
length' EmptyStack = 0
length' (Stk _ t) = 1 + length' t

instance (Eq a) => Eq (Stack a) where
    EmptyStack == EmptyStack = True
    EmptyStack == (Stk _ _)  = False
    (Stk _ _) == EmptyStack  = False
    (Stk a b) == (Stk c d)   = (a == c) && (length' b == length' d)


-- implementar una función recursiva, incluyendo la especificación
-- de su tipo, llamada "exist", que reciba dos argumentos:
--      * una base de datos (valor de tipo "Database")
--      * un libro (valor de tipo Book)
-- y devuelva un valor lógico indicando si el libro existe en DB.

type Person = String
type Book = String
type Database = [(Person, Book)]

exists :: Database -> Book -> Bool
exists [] _ = False
exists ((_,b):dbs) book
    | b == book = True 
    | otherwise = exists dbs book

-- ejercicio 5 boletin ejercicios examen
data Tree a = Leaf a | Branch (Tree a) (Tree a) deriving Show 
type Forest a = [Tree a]

numLeaves :: Tree a -> Int
numLeaves (Leaf x) = 1
numLeaves (Branch a b) = numLeaves a + numLeaves b

countLeaves :: (Eq a) => a -> Tree a -> Int
countLeaves v (Leaf x)
        | v == x = 1
        | otherwise = 0
countLeaves v (Branch a b) = countLeaves v a + countLeaves v b 

forestSize :: Forest a -> Int
forestSize [] = 0
forestSize (x:xs) = numLeaves x + forestSize xs

{-
-------------Alternativa a forestSize-------------
forestSize :: Forest a -> Int
forestSize = sum . (map numLeaves)
-}

-- ejercicio 6 boletin ejercicios examen

--type Person = String
--type Book = String
--type Database = [(Person, Book)]

howMany :: Database -> Book -> Int 
howMany [] _ = 0
howMany ((_,b):dbs) book
        | b == book = 1 + howMany dbs book
        | otherwise = howMany dbs book


-- pregunta 1A, examen 2019
intersect :: (Eq a) => [a] -> [a] -> [a]
intersect [] _ = []
insersect _ [] = []
insersect (x:xs) y
        | member x y = x : intersect xs y
        | otherwise = intersect xs y

-- intersect x y = [z | z <- x, member z y]

-- pregunta 1B, examen 2019
union :: (Eq a) => [a] -> [a] -> [a]
union x [] = x
union [] y = y
union (x:xs) y
        | member x y = union xs y
        | otherwise = x : union xs y

-- union x y = [z | z <- x, not(member z y)] ++ y


-- pregunta 2A, examen 2019
data BinTreeInt = Void | Node Int BinTreeInt BinTreeInt deriving Show

mapTree :: (Int -> Int) -> BinTreeInt -> BinTreeInt
mapTree _ Void = Void
mapTree f (Node n izq der) = Node (f n) (mapTree f izq) (mapTree f der)

sizeTree :: BinTreeInt -> Int
sizeTree Void = 0
sizeTree (Node n izq der) = 1 + sizeTree izq + sizeTree der

-- pregunta 1C, examen 2019
select :: (Int -> Bool) -> [Int] -> [Int]
select _ [] = []
select f (x:xs)
        | f x = x : select f xs
        | otherwise = select f xs

-- select f xs = [y | y <- xs, f y]

-- pregunta 2C, examen 2019
type Side = Float 
data Cube = Cube Side

class Shape3D a where
        area    :: a -> Float
        volume  :: a -> Float

instance Shape3D Cube where
        area (Cube s) = 6 * s**2
        volume (Cube s) = s**3

-- pregunta 1D, examen 2019
operate :: (Int -> Int -> Int) -> [Int] -> [Int] -> [Int]
operate f (x:xs) (y:ys) = (f x y) : operate f xs ys

-- pregunta 2D, examen 2019
type Radius = Float
data Sphere = Sphere Radius

instance Shape3D Sphere where
        area (Sphere r) = 4 * pi * r**2
        volume (Sphere r) = (4/3) * pi * r**3