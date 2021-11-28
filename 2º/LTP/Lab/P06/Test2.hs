import qualified Triangle
import qualified Circle

main = do 
    putStrLn("The area of Circle r=2 is " ++ show (Circle.area 2))
    putStrLn("The area of Triangle b=4 h=5 is " ++ show (Triangle.area 4 5))