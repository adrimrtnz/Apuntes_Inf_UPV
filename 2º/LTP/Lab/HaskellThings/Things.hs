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