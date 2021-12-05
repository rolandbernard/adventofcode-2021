
use std::io;
use std::io::prelude::*;
use std::collections::*;
use std::cmp::*;

fn main() {
    let mut lines = Vec::new();
    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        let inputs: Vec<i32> = line.unwrap().split(" -> ")
            .flat_map(|l|
                l.split(",")
                    .map(|x| x.parse().unwrap())
                    .collect::<Vec<i32>>()
            ).collect();
        lines.push(((inputs[0], inputs[1]), (inputs[2], inputs[3])));
    }
    let mut map = HashMap::<(i32, i32), i32>::new();
    for line in lines {
        if line.0.0 == line.1.0 {
            for i in min(line.0.1, line.1.1)..=max(line.0.1, line.1.1) {
                let pos = (line.0.0, i);
                map.insert(pos, 1 + map.get(&pos).unwrap_or(&0));
            }
        } else if line.0.1 == line.1.1 {
            for i in min(line.0.0, line.1.0)..=max(line.0.0, line.1.0) {
                let pos = (i, line.0.1);
                map.insert(pos, 1 + map.get(&pos).unwrap_or(&0));
            }
        }
    }
    let mut count = 0;
    for (_, &danger) in map.iter() {
        if danger >= 2 {
            count += 1;
        }
    }
    println!("Result: {}", count);
}

