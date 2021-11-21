module ExeP5 where

    -- this function return number x in Binary starting
    -- from the less significant bit
    decBinLSB :: Int -> [Int]
    decBinLSB x | x < 2 = [x]
             | otherwise = (mod x 2) : decBin(div x 2)

    -- this function return number x in Binary
    decBin :: Int-> [Int]
    decBin x = reverse (decBin x)

    binDecReverse :: [Int] -> Int
    binDecReverse (x:[]) = x
    binDecReverse (x:y) = x + binDecReverse y * 2

    binDec :: [Int] -> Int
    binDec x = binDecReverse (reverse x)

    divisors :: Int -> [Int]
    divisors x = [y | y<-[1..x], (mod x y) == 0]

    member :: Int -> [Int] -> Bool
    member x [] = False
    member x y | head y == x = True
               | otherwise = member x (tail y)
    

    isPrime :: Int -> Bool
    isPrime 1 = False
    isPrime x = length (divisors x) < 3

    primes :: Int -> [Int]
    primes 0 = []
    primes x = take x list
        where
         list = [ y | y <- [2..], isPrime y ]
    
    selectEven :: [Int] -> [Int]
    selectEven x = [x !! z | z<-[0..((length x) - 1)], mod (x !! z) 2 == 0]

    selectEvenPos :: [Int] -> [Int]
    selectEvenPos x = [x !! z | z<-[0..((length x) - 1)], mod z 2 == 0]

    iSort :: [Int] -> [Int]
    iSort [] = []
    iSort (x:xs) = ins x (iSort xs)

    ins :: Int -> [Int] -> [Int]
    ins x [] = [x]
    ins x (y:ys) | x < y = x:y:ys
                 | otherwise = y:(ins x ys)

    doubleAll :: [Int] -> [Int]
    doubleAll = map (2*)

    --FALTA: ejercicio 10 map' y filter'