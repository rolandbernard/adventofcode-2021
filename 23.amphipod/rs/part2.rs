
use std::io;
use std::io::prelude::*;
use std::collections::*;

const LENGTH: usize = 11;
const TYPES: usize = 4;
const DEPTH: usize = 4;
const COSTS: [u32; 4] = [1, 10, 100, 1000];
const ROOMS: [u8; 4] = [2, 4, 6, 8];

type GameState = [[[u8; 2]; DEPTH]; TYPES];

fn finished(state: &GameState) -> bool {
    for i in 0..TYPES {
        for j in 0..DEPTH {
            if state[i][j][1] == 0 || state[i][j][0] != ROOMS[i] {
                return false;
            }
        }
    }
    return true;
}

fn can_move(state: &GameState, from: &[u8; 2], to: &[u8; 2]) -> bool {
    if to[1] == 0 {
        for i in 0..TYPES {
            if to[0] == ROOMS[i] {
                return false;
            }
        }
        let mut mov = false;
        'mov: for i in 0..TYPES {
            for j in 0..DEPTH {
                if state[i][j][0] == from[0] && state[i][j][0] != ROOMS[i] {
                    mov = true;
                    break 'mov;
                }
            }
        }
        if !mov {
            return false;
        }
    }
    for i in 0..TYPES {
        for j in 0..DEPTH {
            let x = state[i][j];
            if x[0] != from[0] || x[1] != from[1] {
                if x[1] == 0 && x[0] > u8::min(to[0], from[0]) && x[0] < u8::max(to[0], from[0]) {
                    return false;
                } else if x[0] == from[0] && x[1] <= from[1] {
                    return false;
                } else if x[0] == to[0] && x[1] <= to[1] {
                    return false;
                } else if to[1] != 0 && x[0] == to[0] && x[0] != ROOMS[i] {
                    return false;
                }
            }
        }
    }
    return true;
}

fn moves_for(from: &GameState) -> Vec<(GameState, u32)> {
    let mut res = Vec::new();
    for i in 0..TYPES {
        for j in 0..DEPTH {
            if from[i][j][1] == 0 {
                for h in (1..=DEPTH).rev() {
                    let to = [ROOMS[i], h as u8];
                    if can_move(from, &from[i][j], &to) {
                        let mut next = *from;
                        next[i][j] = to;
                        next[i].sort();
                        res.push((next,
                            COSTS[i] * (
                                i32::abs(from[i][j][0] as i32 - to[0] as i32)
                                + i32::abs(from[i][j][1] as i32 - to[1] as i32)
                            ) as u32
                        ));
                        break;
                    }
                }
            } else {
                for h in 0..LENGTH {
                    let to = [h as u8, 0];
                    if can_move(from, &from[i][j], &to) {
                        let mut next = *from;
                        next[i][j] = to;
                        next[i].sort();
                        res.push((next,
                            COSTS[i] * (
                                i32::abs(from[i][j][0] as i32 - to[0] as i32)
                                + i32::abs(from[i][j][1] as i32 - to[1] as i32)
                            ) as u32
                        ));
                    }
                }
            }
        }
    }
    return res;
}

fn find_minimum(mem: &mut HashMap<GameState, u32>, state: &GameState, max: u32) -> u32 {
    if finished(state) {
        return 0;
    } else if mem.contains_key(state) {
        return *mem.get(state).unwrap();
    } else {
        let mut cost = u32::MAX;
        mem.insert(*state, u32::MAX);
        for (next, c) in moves_for(state) {
            if c < max {
                cost = c + u32::min(cost - c, find_minimum(mem, &next, u32::min(cost, max) - c));
            }
        }
        mem.insert(*state, cost);
        return cost;
    }
}

fn read_input() -> GameState {
    let mut res: GameState = [[[0; 2]; DEPTH]; TYPES];
    let mut ind = [0; TYPES];
    let mut i = 0;
    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        for c in line.unwrap().bytes() {
            if c >= 'A' as u8 && c <= 'D' as u8 {
                let x = c as usize - 'A' as usize;
                res[x][ind[x]][0] = ROOMS[i % TYPES];
                res[x][ind[x]][1] = (1 + 3 * (i / TYPES)) as u8;
                ind[x] += 1; i += 1;
            }
        }
    }
    let f = "DCBA DBAC";
    for c in f.bytes() {
        if c >= 'A' as u8 && c <= 'D' as u8 {
            let x = c as usize - 'A' as usize;
            res[x][ind[x]][0] = ROOMS[i % TYPES];
            res[x][ind[x]][1] = (i / TYPES) as u8;
            ind[x] += 1; i += 1;
        }
    }
    for i in 0..TYPES {
        res[i].sort();
    }
    return res;
}

fn main() {
    let initial = read_input();
    let mut mem = HashMap::new();
    let minimum = find_minimum(&mut mem, &initial, u32::MAX);
    println!("Result: {}", minimum);
}

