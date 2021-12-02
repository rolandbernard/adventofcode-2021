
import System.IO

comb (x, y) (d:as:_) =
    let a = read as :: Integer in
    case d of
        "forward" -> (x + a, y)
        "up" -> (x, y - a)
        "down" -> (x, y + a)

split p s = 
    case dropWhile p s of
        "" -> []
        s' -> w : split p s''
            where (w, s'') = break p s'

main = do
    dat <- readFile "input.txt"
    let slt = map (split (==' ')) (split (=='\n') dat)
    let res = foldl comb (0, 0) slt
    putStrLn ("Location: " ++ show (fst res) ++ " " ++ show (snd res))
    putStrLn ("Result: " ++ show (uncurry (*) res))

