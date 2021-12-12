module Things where

    doubleSmallNumber :: (Num a, Ord a) => a -> a
    doubleSmallNumber x | x > 100 = x
                        | otherwise = x*2
    
    boomBangs :: [Int] -> [String]
    boomBangs xs = [if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]

    quitaMayus :: String -> String
    quitaMayus st = [c | c <- st, c `elem` ['a'..'z']]

    quitaMinusculas :: String -> String
    quitaMinusculas st = [c | c <- st,  c `elem` ['A'..'Z']]

    capital :: String -> String 
    capital "" = "An empty list!"
    capital all@(x:_) = "The first letter of '" ++ all ++ "' es " ++ [x]

    calcBMI :: (RealFloat a) => a -> a -> a
    calcBMI height weight = bmi
        where bmi = weight / (height ^ 2)

    calcBMI' :: (RealFloat a) => (a, a) -> a
    calcBMI' (w, h) =  w / h^2
    
    iniciales :: String -> String -> String 
    iniciales nombre apellido = [n] ++ ". " ++ [a] ++ "."
        where (n:_) = nombre
              (a:_) = apellido

    cilindro :: (RealFloat a) => a -> a -> a
    cilindro r h =
        let areaLado = 2 * pi * r * h
            areaBase = pi * r^2
        in areaLado + 2 * areaBase

    maximum' :: (Ord a) => [a] -> a 
    maximum' [] = error "Maximum of an empty list"
    maximum' [x] = x
    maximum' (x:xs)
        | x > maxTail = x
        | otherwise = maxTail
        where maxTail = maximum' xs

    reverse' :: [a] -> [a]
    reverse' [] = []
    reverse' (x:xs) = reverse' xs ++ [x]

    quicksort :: (Ord a) => [a] -> [a]
    quicksort [] = []
    quicksort (x:xs) =
        let smallerSorted = quicksort[a | a <- xs, a <= x]
            biggerSorted  = quicksort[a | a <- xs, a > x]
        in smallerSorted ++ [x] ++ biggerSorted
        ---( Alternative form with filter )---
        --let smallerSorted = quicksort (filter (<= x) xs)
        --     biggerSorted  = quicksort (filter (> x) xs)
        --in smallerSorted ++ [x] ++ biggerSorted

    applyTwice :: (a -> a) -> a -> a
    applyTwice f x = f (f x)

    largestDivisible :: (Integral a) => a
    largestDivisible = head (filter p [100000, 99999..])
        where p x = x `mod` 3829 == 0

    collatz :: (Integral a) => a -> [a]
    collatz 1 = [1]
    collatz n
            | even n = n:collatz (n `div` 2)
            | odd n = n:collatz (n*3 + 1)

    numLongCollatz :: Int -> Int
    numLongCollatz x = length (filter isLong (map collatz [1..100]))
        where isLong xs = length xs > x

    -- recursive form of sum
    sum' :: (Num a) => [a] -> a
    sum' [] = 0
    sum' (x:xs) = x +  sum xs


    -- sum with foldr function
    sum'' :: (Num a) => [a] -> a
    sum'' = foldl (+) 0