
import System.IO
import Data.List
import Data.Ord
import Data.Char
import Data.Set (Set)
import qualified Data.Set as Set

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

pointsInBasin :: [[Int]] -> Set (Int, Int) -> (Int, Int) -> Set (Int, Int)
pointsInBasin chart s (x, y) =
    if getPoint chart (x, y) == 10 || Set.member (x, y) s then s
    else do
        let s0 = Set.insert (x, y) s
        let s1 = pointsInBasin chart s0 (x, y - 1)
        let s2 = pointsInBasin chart s1 (x, y + 1)
        let s3 = pointsInBasin chart s2 (x - 1, y)
        let s4 = pointsInBasin chart s3 (x + 1, y)
        s4
        
measureBasin chart point = length (pointsInBasin chart Set.empty point)

main = do
    dat <- readFile "input.txt"
    let chart = map (\l -> [10] ++ map (\x -> ord x - ord '0' + 1) l ++ [10]) (split (=='\n') dat)
    let padded = [take (length (head chart)) [10,10..]] ++ chart ++ [take (length (head chart)) [10,10..]]
    let basins = map (measureBasin padded) (findLowPoints padded)
    let x:y:z:_ = sortOn Down basins
    putStrLn ("Result: " ++ show (x * y * z))

