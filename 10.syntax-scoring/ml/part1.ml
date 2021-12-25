
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
    | ')' -> 3
    | ']' -> 57
    | '}' -> 1197
    | '>' -> 25137
    | _ -> 0

let explode s = List.init (String.length s) (String.get s)

let rec scoreLineHelper line stack = 
    match line with
    | [] -> 0
    | (x::xs) ->
        match stack with
        | [] -> 0
        | (t::ts) ->
            if x == '(' || x == '[' || x == '{' || x == '<' then
                scoreLineHelper xs (x::stack)
            else if matching t == x then
                scoreLineHelper xs ts
            else
                scoreFor x

let scoreLine line = scoreLineHelper (explode line) ['?']

let rec sumScore lines =
    match lines with
    | (x::xs) -> scoreLine x + sumScore xs
    | [] -> 0

let main =
    let lines = read_lines in
    Printf.printf "Result: %i\n" (sumScore lines)

