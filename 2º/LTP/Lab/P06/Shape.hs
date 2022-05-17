module Shape where
    type Side = Float
    type Apothem = Float
    type Radius = Float
    type Height = Float
    type Volume = Float
    type Surface = Float

    volumePrism :: (Shape a) => a -> Height -> Volume
    volumePrism base height = (area base) * height
    
    surfacePrism :: (Shape a) => a -> Height -> Surface
    surfacePrism base height = (perimeter base) * height * 2

    data Pentagon = Pentagon Side Apothem
    data Circle = Circle Radius

    class (Eq a, Show a) => Shape a where
        perimeter :: a -> Float
        area :: a -> Float

    instance Shape Pentagon where
        perimeter (Pentagon s a) = 5 * s
        area (Pentagon s a) = 5 * s * a / 2

    instance Shape Circle where
        perimeter (Circle r) = 2 * pi * r
        area (Circle r) = pi * r * r

    instance Eq Pentagon where
        Pentagon a b == Pentagon c d = a == c && b == d

    instance Eq Circle where
        Circle a == Circle b = a == b

    instance Show Pentagon where
        show (Pentagon a b) = "Pentagon of side " ++ show a ++ " and apothem " ++ show b 
    
    instance Show Circle where
        show (Circle a) = "Circle of radius " ++ show a 