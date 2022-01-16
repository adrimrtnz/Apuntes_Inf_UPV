module Arboles where

    data BinTreeInt = Void | Node Int BinTreeInt BinTreeInt deriving Show
    data Tree a = Leaf a | Branch (Tree a) (Tree a) deriving Show

    numleaves :: Tree a -> Int
    numleaves (Leaf x) = 1
    numleaves (Branch a b) = numleaves a + numleaves b

    symmetric :: Tree a -> Tree a 
    symmetric (Leaf a) = Leaf a
    symmetric (Branch a b) = Branch (symmetric b) (symmetric a)

    listToTree :: [a] -> Tree a
    listToTree [x] = Leaf x
    listToTree (x:xs) = Branch (Leaf x) (listToTree xs)

    treeToList :: Tree a -> [a]
    treeToList (Leaf x) = [x]
    treeToList (Branch a b) = (treeToList a) ++ (treeToList b)

    insTree :: Int -> BinTreeInt -> BinTreeInt
    insTree n Void = Node n Void Void
    insTree n (Node x izq der)
        | n > x = Node x izq (insTree n der)
        | otherwise = Node x (insTree n izq) der

    creaTree :: [Int] -> BinTreeInt
    creaTree [] = Void
    creaTree [x] = insTree x Void
    creaTree (x:xs) = insTree x (creaTree xs)

    treeElem :: Int -> BinTreeInt -> Bool 
    treeElem _ Void = False
    treeElem x (Node y izq der)
            | x == y = True 
            | x < y = treeElem x izq
            | otherwise = treeElem x der