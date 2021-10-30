module Hello where
    hello:: Int -> [Char]
    hello n = concat (replicate n "hello ")