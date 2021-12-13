
import System.IO
import Data.List.Split
import Data.Set (Set)
import qualified Data.Set as Set

applyFold points (d, v) =
    if d == 'x' then
        map (\(x, y) -> if x > v then (2*v - x, y) else (x, y)) points
    else
        map (\(x, y) -> if y > v then (x, 2*v - y) else (x, y)) points

main = do
    dat <- readFile "input.txt"
    let (rawpoints:rawfolds:_) = splitOn [""] (splitOn "\n" dat)
    let points = map ((\(x:y:_) -> (x, y)) . map (read :: String -> Int) . splitOn ",") rawpoints
    let folds = map ((\(d:v:_) -> (last d, read v :: Int)) . splitOn "=") rawfolds
    putStrLn ("Result: " ++ show (length (Set.fromList (applyFold points (head folds)))))

