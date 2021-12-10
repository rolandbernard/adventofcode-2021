
import System.IO
import Data.Char
import Data.List

split p s =
    case dropWhile p s of
        "" -> []
        s' -> w : split p s''
            where (w, s'') = break p s'

matching x = case x of
    '(' -> ')'
    '[' -> ']'
    '{' -> '}'
    '<' -> '>'
    _ -> '?'

scoreFor x = case x of
    '(' -> 1
    '[' -> 2
    '{' -> 3
    '<' -> 4
    _ -> 0

missingElementsHelper "" s = s
missingElementsHelper (x:xs) (t:ts)
  | x == '(' || x == '[' || x == '{' || x == '<'
    = missingElementsHelper xs (x:t:ts)
  | matching t == x
    = missingElementsHelper xs ts
  | otherwise
    = []

missingElements line = missingElementsHelper line "?"

main = do
    dat <- readFile "input.txt"
    let results = map missingElements (split (=='\n') dat)
    let result = map (foldl (\x y -> 5 * x + scoreFor y) 0) (filter (/="") results)
    let sorted = sort result
    putStrLn ("Result: " ++ show ((sorted !! (length sorted `div` 2)) `div` 5))
