
use std::io;
use std::io::prelude::*;

fn main() {
    let stdin = io::stdin();
    let mut count = 0;
    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let inputs: Vec<&str> = line.split(" | ")
            .flat_map(|l| l.split(" ").collect::<Vec<&str>>()).collect();
        let mut freq: [i32; 7] = [0; 7];
        for i in 0..10 {
            for c in inputs[i].chars() {
                freq[c as usize - 'a' as usize] += 1;
            }
        }
        let mut value = 0;
        for i in 10..14 {
            let sum = inputs[i].chars()
                .map(|c| freq[c as usize - 'a' as usize]).sum();
            value *= 10;
            value += match sum {
                42 => 0, 17 => 1, 34 => 2,
                39 => 3, 30 => 4, 37 => 5,
                41 => 6, 25 => 7, 49 => 8,
                45 => 9, _ => 0,
            };
        }
        count += value;
    }
    println!("Result: {}", count);
}

