
open System

type Number =
    | Regular of int
    | Pair of Number * Number

let rec parseHelper (str: string) =
    if str.[0] = '[' then
        let (left, left_rest: string) = parseHelper str.[1..]
        let (right, right_rest: string) = parseHelper left_rest.[1..]
        (Pair(left, right), right_rest.[1..])
    else
        let split = str.IndexOfAny [|','; ']'|]
        (Regular(int str.[..split - 1]), str.[split..])

let parse string =
    let (number, _) = parseHelper string
    number

let rec addFirst number dx =
    match number with
    | Regular(x) -> Regular(x + dx)
    | Pair(x, y) -> Pair(addFirst x dx, y)

let rec addLast number dx =
    match number with
    | Regular(x) -> Regular(x + dx)
    | Pair(x, y) -> Pair(x, addLast y dx)

let rec explodeStep number depth =
    match number with
    | Regular(x) -> (false, Regular(x), 0, 0)
    | Pair(Regular(l), Regular(r)) when depth >= 4 -> (true, Regular(0), l, r)
    | Pair(l, r) ->
        let (lc, left, llc, lrc) = explodeStep l (depth + 1)
        if lc then
            (true, Pair(left, addFirst r lrc), llc, 0)
        else
            let (rc, right, rlc, rrc) = explodeStep r (depth + 1)
            if rc then
                (true, Pair(addLast l rlc, right), 0, rrc)
            else
                (false, Pair(l, r), 0, 0)

let rec splitStep number =
    match number with
    | Regular(x) ->
        if x >= 10 then
            (true, Pair(Regular(x / 2), Regular((x + 1) / 2)))
        else
            (false, Regular(x))
    | Pair(l, r) ->
        let (lc, left) = splitStep l
        if lc then
            (true, Pair(left, r))
        else
            let (rc, right) = splitStep r
            if rc then
                (true, Pair(l, right))
            else
                (false, Pair(l, r))

let rec reduce number =
    let (ec, ered, _, _) = explodeStep number 0
    if ec then
        reduce ered
    else
        let (sc, sred) = splitStep number
        if sc then
            reduce sred
        else
            number

let add a b = reduce (Pair(a, b))

let rec magnitude number =
    match number with
    | Regular(i) -> i
    | Pair(x, y) -> (3 * magnitude x) + (2 * magnitude y)

let rec maxIn list =
    match list with
    | (x::xs) -> max x (maxIn xs)
    | [] -> 0

let raw = Console.In.ReadToEnd()
let numbers = [for n in raw.Split '\n' do if not (String.IsNullOrEmpty n) then yield parse n]

let max = maxIn [for x in numbers do for y in numbers do if x <> y then yield magnitude (add x y)]

printfn "Result: %i" max

