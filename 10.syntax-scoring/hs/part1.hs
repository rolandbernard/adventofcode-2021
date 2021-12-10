
import System.IO
import Data.Char

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
    ')' -> 3
    ']' -> 57
    '}' -> 1197
    '>' -> 25137
    _ -> 0

scoreLineHelper "" _ = 0
scoreLineHelper (x:xs) (t:ts)
  | x == '(' || x == '[' || x == '{' || x == '<'
    = scoreLineHelper xs (x:t:ts)
  | matching t == x
    = scoreLineHelper xs ts
  | otherwise
    = scoreFor x

scoreLine line = scoreLineHelper line "?"

main = do
    dat <- readFile "input.txt"
    let results = map scoreLine (split (=='\n') dat)
    putStrLn ("Result: " ++ show (sum results))

