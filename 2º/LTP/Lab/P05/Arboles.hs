module Arboles where

    data BinTreeInt = Void | Node Int BinTreeInt BinTreeInt deriving Show
    data Tree a = Leaf a | Branch (Tree a) (Tree a) deriving Show

    numleaves :: Tree a -> Int
    numleaves (Leaf x) = 1
    numleaves (Branch a b) = numleaves a + numleaves b

    symmetric :: Tree a -> Tree a 
    symmetric (Leaf a) = (Leaf a)
    symmetric (Branch a b) = Branch (symmetric b) (symmetric a)

    listToTree :: [a] -> Tree a
    listToTree [x] = Leaf x
    listToTree (x:xs) = Branch (Leaf x) (listToTree xs)

    treeToList :: Tree a -> [a]
    treeToList (Leaf x) = [x]
    treeToList (Branch a b) = (treeToList a) ++ (treeToList b) 