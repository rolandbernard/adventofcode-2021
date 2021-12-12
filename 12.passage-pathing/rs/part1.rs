
use std::io;
use std::io::prelude::*;
use std::collections::*;

struct Map {
    mapping: HashMap<String, usize>,
    small: Vec<bool>,
    connections: Vec<Vec<usize>>,
}

fn get_mapping(map: &mut Map, name: &str) -> usize {
    if !map.mapping.contains_key(name) {
        map.mapping.insert(name.to_string(), map.mapping.len());
        map.small.push(name == name.to_lowercase());
        map.connections.push(Vec::new());
    }
    return *map.mapping.get(name).unwrap();
}

fn count_paths(map: &mut Map, visited: &mut Vec<bool>, at: usize, end: usize) -> usize {
    if at == end {
        return 1;
    } else if map.small[at] && visited[at] {
        return 0;
    } else {
        let mut ret = 0;
        visited[at] = true;
        for i in map.connections[at].clone().iter() {
            ret += count_paths(map, visited, *i, end);
        }
        visited[at] = false;
        return ret;
    }
}

fn main() {
    let mut map = Map {
        mapping: HashMap::new(),
        small: Vec::new(),
        connections: Vec::new(),
    };
    let start = get_mapping(&mut map, "start");
    let end = get_mapping(&mut map, "end");
    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        let line = line.unwrap();
        let inputs = line.split("-").collect::<Vec<&str>>();
        let from = get_mapping(&mut map, inputs[0]);
        let to = get_mapping(&mut map, inputs[1]);
        map.connections[from].push(to);
        map.connections[to].push(from);
    }
    let mut visited = std::iter::repeat(false).take(map.mapping.len()).collect();
    let count = count_paths(&mut map, &mut visited, start, end);
    println!("Result: {}", count);
}

