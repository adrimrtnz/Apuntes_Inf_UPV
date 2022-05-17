import Shape
main = do
    let c = (Circle 5)
    let p = (Pentagon 5 4)
    putStrLn("Perimeter of Circle is " ++ show (perimeter c));
    putStrLn("Area of Circle is " ++ show (area c));
    putStrLn("Perimeter of Pentagon is " ++ show (perimeter p));
    putStrLn("Area of Pentagon is " ++ show (area p));