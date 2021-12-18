
import Data.List.Split
import Data.Char

data Number = Int Int | Pair (Number, Number) deriving (Show)

parseHelper ('[':xs) = (Pair (first, second), tail rest)
    where
        (first, rest') = parseHelper xs
        (second, rest) = parseHelper (tail rest')
parseHelper string = (Int (read number), rest)
    where (number, rest) = span isDigit string

parse string = number
    where (number, _) = parseHelper string

applyFirst (Int x) dx = (Int (x + dx), 0)
applyFirst (Pair (x, y)) d = (Pair (x', y'), d'')
    where
        (x', d') = applyFirst x d
        (y', d'') = applyFirst y d'

applyLast (Int x) dx = (Int (x + dx), 0)
applyLast (Pair (x, y)) d = (Pair (x', y'), d'')
    where
        (y', d') = applyLast y d
        (x', d'') = applyLast x d'

magn (Int i) = i
magn (Pair (x, y)) = (3 * magn x) + (2 * magn y)

explodeStep (Int i) _ = (False, Int i, 0, 0)
explodeStep (Pair (Int l, Int r)) d
    | d >= 4 = (True, Int 0, l, r)
explodeStep (Pair (l, r)) d
    | b = (True, Pair (x, r'), dl, ddr')
    | b' = (True, Pair (l', x'), ddl', dr')
    | otherwise = (False, Pair (l, r), 0, 0)
    where
        (b, x, dl, dr) = explodeStep l (d + 1)
        (b', x', dl', dr') = explodeStep r (d + 1)
        (r', ddr') = applyFirst r dr
        (l', ddl') = applyLast l dl'

splitNumber i
    | even i = (Int (i `div` 2), Int (i `div` 2))
    | otherwise = (Int (i `div` 2), Int ((i `div` 2) + 1))

splitStep (Int i)
    | i >= 10 = (True, Pair (splitNumber i))
    | otherwise = (False, Int i)
splitStep (Pair (l, r))
    | b = (True, Pair (l', r))
    | b' = (True, Pair (l, r'))
    | otherwise = (False, Pair (l, r))
    where
        (b, l') = splitStep l
        (b', r') = splitStep r

reduceStep x
    | r = (True, x')
    | r' = (True, x'')
    | otherwise = (False, x)
    where
        (r, x', _, _) = explodeStep x 0
        (r', x'') = splitStep x

reduce x = if r then reduce x' else x
    where (r, x') = reduceStep x

add a b = reduce (Pair (a, b))

main = do
    dat <- getContents
    let numbers = map parse (filter (not . null) (splitOn "\n" dat)) :: [Number]
    let mmax = foldl max 0 [magn (add x y) | x <- numbers, y <- numbers]
    putStrLn ("Result: " ++ show mmax)

