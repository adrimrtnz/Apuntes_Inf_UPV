module Signum where
    --Definición de la función signum' (signo):
    signum' :: Int -> Int
    signum' x = if x < 0 then -1 else
                if x == 0 then 0 else 1
    
    signum''::Int -> Int
    signum'' x
            | x < 0     = -1
            | x == 0    = 0
            | otherwise = 1