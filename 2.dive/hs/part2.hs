
import System.IO

split p s = 
    case dropWhile p s of
        "" -> []
        s' -> w : split p s''
            where (w, s'') = break p s'

move p _ [] = p
move (x, y) a ((d:vs:_):is) =
    let v = read vs :: Integer in
    case d of
        "forward" -> move (x + v, y + v * a) a is
        "up" -> move (x, y) (a - v) is
        "down" -> move (x, y) (a + v) is

main = do
    dat <- readFile "input.txt"
    let slt = map (split (==' ')) (split (=='\n') dat)
    let res = move (0, 0) 0 slt
    putStrLn ("Location: " ++ show (fst res) ++ " " ++ show (snd res))
    putStrLn ("Result: " ++ show (uncurry (*) res))

