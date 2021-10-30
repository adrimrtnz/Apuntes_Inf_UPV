module ExeP4 where
    import Data.Char

    fact :: Int -> Int
    fact 0 = 1
    fact n = n * fact (n - 1)

    numCbetw2 :: Char -> Char -> Int
    numCbetw2 c1 c2 
                    | c1 == c2 = 0
                    | otherwise = abs (ord c2 - ord c1) - 1
    
    addRange :: Int -> Int -> Int
    addRange x y | y == x = y
                 | y < x = addRange y x
                 | otherwise = y + addRange x (y-1)

    max' :: Int -> Int -> Int
    max' x y | x > y = x
             | otherwise = y

    leapyear :: Int -> Bool
    leapyear y = mod y 4 == 0 
                 && (mod y 100 /= 0 || mod y 400 == 0)

    daysAmonth :: Int -> Int -> Int
    daysAmonth m y  | m == 2 && leapyear y = 29
                    | not (m == 2 && leapyear y) = 28
                    | [x | x<-[1,3,5,7,8,10,12], x==m]  /= [] = 31
                    | otherwise = 30
    
    remainder :: Int -> Int -> Int
    remainder x y = mod x y

    sumFacts :: Int -> Int
    sumFacts x = fact x + fact (x-1)