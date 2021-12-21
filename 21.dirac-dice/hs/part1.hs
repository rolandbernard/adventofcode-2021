
import Data.List.Split

dice s i = ((3*s + 1) `mod` 100) + 1

applyStep l@(l0, l1) p@(p0, p1) s =
    if even s then
        ((l0', l1), (p0 + l0', p1), s + 1)
    else
        ((l0, l1'), (p0, p1 + l1'), s + 1)
    where
        d = dice s 0 + dice s 1 + dice s 2
        l0' = ((l0 + d - 1) `mod` 10) + 1
        l1' = ((l1 + d - 1) `mod` 10) + 1

call f (a, b, c) = f a b c

play l p@(p0, p1) s
    | p0 >= 1000 = (p1, 3 * s)
    | p1 >= 1000 = (p0, 3 * s)
    | otherwise = call play (applyStep l p s)

single x = [x]
tuple (x:y:_) = (x, y)

main = do
    dat <- getContents
    let start = tuple (map (read . single . last) (filter (not . null) (splitOn "\n" dat)) :: [Int])
    let result = play start (0, 0) 0
    putStrLn ("Result: " ++ show (uncurry (*) result))

