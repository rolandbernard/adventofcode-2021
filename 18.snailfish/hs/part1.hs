
import Data.List.Split
import Data.Char

data Number = Int Int | Pair Number Number deriving (Eq, Show)

parseHelper ('[':xs) = (Pair first second, tail rest)
    where
        (first, rest') = parseHelper xs
        (second, rest) = parseHelper (tail rest')
parseHelper string = (Int (read number), rest)
    where (number, rest) = span isDigit string

parse string = number
    where (number, _) = parseHelper string

addFirst (Int x) dx = Int (x + dx)
addFirst (Pair x y) d = Pair (addFirst x d) y

addLast (Int x) dx = Int (x + dx)
addLast (Pair x y) d = Pair x (addLast y d)

explodeStep (Int i) _ = (False, Int i, 0, 0)
explodeStep (Pair (Int l) (Int r)) d
    | d >= 4 = (True, Int 0, l, r)
explodeStep (Pair l r) d
    | b = (True, Pair x (addFirst r dr), dl, 0)
    | b' = (True, Pair (addLast l dl') x', 0, dr')
    | otherwise = (False, Pair l r, 0, 0)
    where
        (b, x, dl, dr) = explodeStep l (d + 1)
        (b', x', dl', dr') = explodeStep r (d + 1)

splitStep (Int i)
    | i >= 10 = (True, Pair (Int (i `div` 2)) (Int ((i + 1) `div` 2)))
    | otherwise = (False, Int i)
splitStep (Pair l r)
    | b = (True, Pair l' r)
    | b' = (True, Pair l r')
    | otherwise = (False, Pair l r)
    where
        (b, l') = splitStep l
        (b', r') = splitStep r

reduce x
    | r = reduce x'
    | r' = reduce x''
    | otherwise = x
    where
        (r, x', _, _) = explodeStep x 0
        (r', x'') = splitStep x

add a b = reduce (Pair a b)

magn (Int i) = i
magn (Pair x y) = (3 * magn x) + (2 * magn y)

main = do
    dat <- getContents
    let numbers = map parse (filter (not . null) (splitOn "\n" dat)) :: [Number]
    let sum = foldl1 add numbers
    putStrLn ("Result: " ++ show (magn sum))

