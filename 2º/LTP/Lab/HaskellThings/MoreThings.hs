module MoreThings where
    import Data.List( nub )

    -- data Nat = Zero | Succ !Nat
    -- ! is known as 'strictness flag'
    data Nat = Zero | Succ Nat

    instance Eq Nat where
        Zero == Zero    = True
        Zero == Succ n  = False
        Succ m == Zero  = False 
        Succ m == Succ n = (m == n)

    instance Show Nat where
        show Zero            = "Zero"
        show (Succ Zero)     = "Succ Zero"
        show (Succ (Succ n)) = "Succ (" ++ show (Succ n) ++ ")"

    instance Num Nat where
        m + Zero     = m
        m + Succ n   = Succ (m + n)

        m * Zero     = Zero
        m * (Succ n) = m * n + m

        abs n           = n
        signum Zero     = Zero
        signum (Succ n) = Succ Zero

        m - Zero        = m
        Zero - Succ n   = Zero
        Succ m - Succ n = m - n

        fromInteger x
            | x <= 0 = Zero
            | otherwise = Succ (fromInteger (x - 1))

    -- nub toma una lista y devuelve otra sin elementos duplicados
    numUniques :: (Eq a) => [a] -> Int
    numUniques = length . nub

    -- Express subtract using flip
    -- flip (-) x y
    
    dobleFactorial :: Integer -> Integer 
    dobleFactorial 0 = 1
    dobleFactorial 1 = 1
    dobleFactorial n = n * (dobleFactorial (n - 2))

    potencia :: Integer -> Integer -> Integer 
    potencia _ 0 = 1
    potencia x n 
            | odd n = x * (potencia x (div n 2)) * (potencia x (div n 2))
            | otherwise = (potencia x (div n 2)) * (potencia x (div n 2))

    numeroBloquesR :: Integer -> Integer
    numeroBloquesR n 
            | n < 1 = 0
            | otherwise = (n * 2) + numeroBloquesR (n-1)

    numeroBloquesC :: Integer -> Integer
    numeroBloquesC n = sum [x*2 | x <- [1..n]] 
