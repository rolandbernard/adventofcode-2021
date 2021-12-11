
import System.IO
import Data.Char

split p s = 
    case dropWhile p s of
        "" -> []
        s' -> w : split p s''
            where (w, s'') = break p s'

getPoint map (x, y) = (map !! x) !! y

isLowPoint map (x, y) = p < a && p < b && p < l && p < r
    where
        p = getPoint map (x, y)
        a = getPoint map (x, y - 1)
        b = getPoint map (x, y + 1)
        l = getPoint map (x - 1, y)
        r = getPoint map (x + 1, y)

findLowPoints chart = filter (isLowPoint chart) ([(x, y) | x <- [1..width], y <- [1..height]])
    where
        width = length chart - 2
        height = length (head chart) - 2

main = do
    dat <- readFile "input.txt"
    let chart = map (\l -> [10] ++ map (\x -> ord x - ord '0' + 1) l ++ [10]) (split (=='\n') dat)
    let padded = [take (length (head chart)) [10,10..]] ++ chart ++ [take (length (head chart)) [10,10..]]
    let result = sum (map (getPoint padded) (findLowPoints padded))
    putStrLn ("Result: " ++ show result)

