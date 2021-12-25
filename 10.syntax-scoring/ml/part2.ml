
let read_lines =
    let lines = ref [] in
    try
        while true; do
            lines := input_line stdin :: !lines
        done; []
    with End_of_file ->
        List.rev !lines

let matching x =
    match x with
    | '(' -> ')'
    | '[' -> ']'
    | '{' -> '}'
    | '<' -> '>'
    | _ -> '?'

let scoreFor x =
    match x with
    | '(' -> 1
    | '[' -> 2
    | '{' -> 3
    | '<' -> 4
    | _ -> 0

let explode s = List.init (String.length s) (String.get s)

let rec missingElementsHelper line stack = 
    match line with
    | [] -> stack
    | (x::xs) ->
        match stack with
        | [] -> []
        | (t::ts) ->
            if x == '(' || x == '[' || x == '{' || x == '<' then
                missingElementsHelper xs (x::stack)
            else if matching t == x then
                missingElementsHelper xs ts
            else
                []

let missingElements line = missingElementsHelper (explode line) ['?']

let rec scoreForElementsHelper elems acc =
    match elems with
    | [] -> acc
    | (x::xs) -> scoreForElementsHelper xs (5 * acc + scoreFor x)

let scoreForElements elems = (scoreForElementsHelper elems 0) / 5

let rec findScores lines =
    match lines with
    | (x::xs) ->
        let score = scoreForElements (missingElements x) in
        if score == 0 then
            findScores xs
        else
            score :: findScores xs
    | [] -> []

let medianScore scores = List.nth (List.sort (-) scores) (List.length scores / 2)

let main =
    let lines = read_lines in
    Printf.printf "Result: %i\n" (medianScore (findScores lines))

