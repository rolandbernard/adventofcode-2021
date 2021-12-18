
use std::io;
use std::io::prelude::*;

fn parse_line(line: &str) -> Vec<(i32, i32)> {
    let mut number = Vec::new();
    let mut depth = 0;
    let mut i = 0;
    while i < line.len() {
        let c = line.as_bytes()[i] as char;
        if c.is_digit(10) {
            let from = i;
            let mut to = i + 1;
            while (line.as_bytes()[to] as char).is_digit(10) {
                to += 1;
            }
            number.push((line[from..to].parse().unwrap(), depth));
            i = to;
        } else {
            if c == '[' {
                depth += 1;
            } else if c == ']' {
                depth -= 1;
            }
            i += 1;
        }
    }
    return number;
}

fn explode_all(number: &mut Vec<(i32, i32)>) -> bool {
    let mut i = 0;
    let mut j = 0;
    while i < number.len() {
        if number[i].1 > 4 {
            if i > 0 {
                number[j - 1].0 += number[i].0;
            }
            if i < number.len() - 2 {
                number[i + 2].0 += number[i + 1].0;
            }
            number[j] = (0, number[i].1 - 1);
            j += 1;
            i += 2;
        } else {
            number[j] = number[i];
            i += 1; j += 1;
        }
    }
    number.resize(j, (0, 0));
    return i != j;
}

fn split_first(number: &mut Vec<(i32, i32)>) -> bool {
    for i in 0..number.len() {
        if number[i].0 >= 10 {
            number.insert(i + 1, ((number[i].0 + 1) / 2, number[i].1 + 1));
            number[i].0 /= 2;
            number[i].1 += 1;
            return true;
        }
    }
    return false;
}

fn normalize(number: &mut Vec<(i32, i32)>) {
    while {explode_all(number); split_first(number)} { }
}

fn add_into(acc: &mut Vec<(i32, i32)>, b: &mut Vec<(i32, i32)>) {
    acc.append(b);
    for i in 0..acc.len() {
        acc[i].1 += 1;
    }
    normalize(acc);
}

fn magnitude(number: &Vec<(i32, i32)>) -> i32 {
    let mut stack = Vec::new();
    for v in number {
        stack.push(*v);
        let mut sp = stack.len() - 1;
        while stack.len() >= 2 && stack[sp].1 == stack[sp - 1].1 {
            stack[sp - 1] = (3 * stack[sp - 1].0 + 2 * stack[sp].0, stack[sp].1 - 1);
            stack.pop();
            sp -= 1;
        }
    }
    return stack[0].0;
}

fn main() {
    let mut numbers = Vec::new();
    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        let line = line.unwrap();
        numbers.push(parse_line(&line));
    }
    let (acc, rest) = numbers.split_at_mut(1);
    for i in 0..rest.len() {
        add_into(&mut acc[0], &mut rest[i]);
    }
    println!("Result: {}", magnitude(&acc[0]));
}

