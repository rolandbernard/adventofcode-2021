
use std::io;
use std::io::prelude::*;

fn main() {
    let stdin = io::stdin();
    let mut count = 0;
    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let inputs: Vec<&str> = line.split(" | ")
            .flat_map(|l| l.split(" ").collect::<Vec<&str>>()).collect();
        for i in 10..14 {
            if [2, 3, 4, 7].contains(&inputs[i].len()) {
                count += 1;
            }
        }
    }
    println!("Result: {}", count);
}

