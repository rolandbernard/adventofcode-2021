
import System.IO
import Data.Char

split p s = 
    case dropWhile p s of
        "" -> []
        s' -> w : split p s''
            where (w, s'') = break p s'
            
replaceAtList _ _ [] = []
replaceAtList n _ xs
    | n < 0 = xs
replaceAtList 0 a (_:xs) = a:xs
replaceAtList number a (x:xs) = x : replaceAtList (number-1) a xs

replaceAtMatrix _ _ [] = []
replaceAtMatrix (m, _) _ xs
    | m < 0 = xs
replaceAtMatrix (0,num2) a (x:xs) = replaceAtList num2 a x : xs
replaceAtMatrix (num1,num2) a (x:xs) = x : replaceAtMatrix (num1-1,num2) a xs

atMatrix (x, y) a = (a !! x) !! y

energize chart (x, y) =
    if x >= 0 && y >= 0 && x < width && y < height && atMatrix (x, y) chart < 10 then
        if atMatrix (x, y) chart == 9 then
            foldl energize (replaceAtMatrix (x, y) (atMatrix (x, y) chart + 1) chart)
                (map (\(i, j) -> (i + x, j + y)) (filter (\(x, y) -> x /= 0 || y /= 0) [(x, y) | x <- [-1..1], y <- [-1..1]]))
        else replaceAtMatrix (x, y) (atMatrix (x, y) chart + 1) chart
    else chart
    where 
        width = length chart
        height = length (head chart)

applyStep chart = (map (map (\x -> if x > 9 then 0 else x)) energized, foldl (foldl (\x y -> if y > 9 then x + 1 else x)) 0 energized)
    where
        energized = foldl energize chart [(x, y) | x <- [0..width], y <- [0..height]]
        width = length chart
        height = length (head chart)

completeFlash chart = 
    if flashes == width * height then 1
    else steps + 1
    where
        (stepped, flashes) = applyStep chart
        steps = completeFlash stepped
        width = length chart
        height = length (head chart)

main = do
    dat <- readFile "input.txt"
    let chart = map (map (\x -> ord x - ord '0')) (split (=='\n') dat)
    let steps = completeFlash chart
    putStrLn ("Result: " ++ show steps)
