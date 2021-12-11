
use std::io;
use std::io::prelude::*;

fn energize(chart: &mut Vec<Vec<u32>>, i: i32, j: i32) {
    if i >= 0 && j >= 0 && i < chart.len() as i32 && j < chart[0].len() as i32 && chart[i as usize][j as usize] < 10 {
        chart[i as usize][j as usize] += 1;
        if chart[i as usize][j as usize] >= 10 {
            for di in -1..=1 {
                for dj in -1..=1 {
                    if di != 0 || dj != 0 {
                        energize(chart, i + di, j + dj);
                    }
                }
            }
        }
    }
}

fn main() {
    let mut chart = Vec::new();
    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        let inputs: Vec<u32> = line.unwrap().chars()
            .map(|x| x.to_digit(10).unwrap())
            .collect::<Vec<u32>>();
        chart.push(inputs);
    }
    let mut flashes = 0;
    for _ in 0..100 {
        for i in 0..chart.len() {
            for j in 0..chart[i].len() {
                energize(&mut chart, i as i32, j as i32);
            }
        }
        for i in 0..chart.len() {
            for j in 0..chart[i].len() {
                if chart[i][j] >= 10 {
                    chart[i][j] = 0;
                    flashes += 1;
                }
            }
        }
    }
    println!("Result: {}", flashes);
}

