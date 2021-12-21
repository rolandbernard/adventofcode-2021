
import Data.List.Split
import qualified Data.HashMap.Strict as HashMap

applyStep ((l0, l1),(p0, p1), t) d =
    if t == 0 then
        ((l0', l1), (p0 + l0', p1), 1 - t)
    else
        ((l0, l1'), (p0, p1 + l1'), 1 - t)
    where
        l0' = ((l0 + d - 1) `mod` 10) + 1
        l1' = ((l1 + d - 1) `mod` 10) + 1

call f (a, b, c) = f a b c

reduce m [] = (m, (0, 0))
reduce m (s:xs) = (m'', (a + a', b + b'))
    where
        (m', (a, b)) = universes m s
        (m'', (a', b')) = reduce (HashMap.insert s (a, b) m') xs

universes m s@(l, (p0, p1), t)
    | p0 >= 21 = (m, (1, 0))
    | p1 >= 21 = (m, (0, 1))
    | otherwise =
        case HashMap.lookup s m of
            Just k -> (m, k)
            Nothing -> reduce m [applyStep s (x + y + z) | x <- [1 .. 3], y <- [1 .. 3], z <- [1 .. 3]]

single x = [x]
tuple (x:y:_) = (x, y)

main = do
    dat <- getContents
    let start = tuple (map (read . single . last) (filter (not . null) (splitOn "\n" dat)) :: [Int])
    let (_, res) = universes HashMap.empty (start, (0, 0), 0 :: Int)
    putStrLn ("Result: " ++ show (uncurry max res))

