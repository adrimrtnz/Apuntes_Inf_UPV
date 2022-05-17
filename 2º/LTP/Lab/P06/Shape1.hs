module Shape1 where

    type Side = Float
    type Apothem = Float
    type Radius = Float

    data Pentagon = Pentagon Side Apothem
    data Circle = Circle Radius

    class Shape a where
        perimeter :: a -> Float

    instance Shape Pentagon where
        perimeter (Pentagon s a) = 5 * s

    instance Shape Circle where
        perimeter (Circle r) = 2 * pi * r
