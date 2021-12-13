
import System.IO
import Data.List.Split
import Data.List
import Data.Set (Set)
import qualified Data.Set as Set

applyFold points (d, v) =
    if d == 'x' then
        map (\(x, y) -> if x > v then (2*v - x, y) else (x, y)) points
    else
        map (\(x, y) -> if y > v then (x, 2*v - y) else (x, y)) points

tupleDo f (a, b) (c, d) = (f a c, f b d)

main = do
    dat <- readFile "input.txt"
    let (rawpoints:rawfolds:_) = splitOn [""] (splitOn "\n" dat)
    let points = map ((\(x:y:_) -> (x, y)) . map (read :: String -> Int) . splitOn ",") rawpoints
    let folds = map ((\(d:v:_) -> (last d, read v :: Int)) . splitOn "=") rawfolds
    let folded = Set.fromList (foldl applyFold points folds)
    let minp = foldl (tupleDo min) (Set.elemAt 1 folded) folded
    let maxp = foldl (tupleDo max) (Set.elemAt 1 folded) folded
    putStrLn ("Result: \n" ++ 
        intercalate "\n" [
            intercalate "" [
                if Set.member (x, y) folded then "##" else "  "
                | x <- [fst minp..fst maxp]
            ] | y <- [snd minp..snd maxp]
        ])

