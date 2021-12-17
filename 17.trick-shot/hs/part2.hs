
import Data.List.Split

moveStep (x, y, dx, dy) = (x + dx, y + dy, dx - signum dx, dy - 1)

steps state = (x, y, dx, dy) : steps (moveStep state)
    where (x, y, dx, dy) = state

isPossibleDx params dx =
    any (\(x, _, _, _) -> x >= minx) (takeWhile (\(x, _, dx, _) -> dx /= 0 && x <= maxx) (steps (0, 0, dx, 0)))
    where (minx, maxx, _, _) = params

possibleDx params = filter (isPossibleDx params) [min 0 minx..max 0 maxx]
    where (minx, maxx, _, _) = params

isPossibleDy params dy =
    any (\(_, y, _, _) -> y <= maxy) (takeWhile (\(_, y, _, _) -> y >= miny) (steps (0, 0, 0, dy)))
    where (_, _, miny, maxy) = params

possibleDy params = filter (isPossibleDy params) [min 0 miny..max (-miny - 1)  maxy]
    where (_, _, miny, maxy) = params

isPossible params (dx, dy) =
    any (\(x, y, _, _) -> minx <= x && x <= maxx && miny <= y && y <= maxy) (takeWhile (\(_, y, _, _) -> y >= miny) (steps (0, 0, dx, dy)))
    where (minx, maxx, miny, maxy) = params

main = do
    dat <- getContents
    let ((minx:maxx:_):(miny:maxy:_):_) = map (map read . splitOn ".." . (!!1) . splitOn "=") (splitOn ", " (splitOn ": " dat !! 1)) :: [[Int]]
    let params = (minx, maxx, miny, maxy)
    let possible = [(dx, dy) | dx <- possibleDx params, dy <- possibleDy params, isPossible params (dx, dy)]
    putStrLn ("Result: " ++ show (length possible))

