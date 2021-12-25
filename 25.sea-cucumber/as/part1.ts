
class Map {
    buffer: Uint8Array;
    width: i32;
    height: i32;

    constructor(width: i32, height: i32) {
        this.width = width;
        this.height = height;
        this.buffer = new Uint8Array(width * height);
    }

    static fromString(input: string): Map {
        const cells: string[][] =
            input.trim().split('\n')
            .map<string[]>(line => line.split(''));
        const map = new Map(cells[0].length, cells.length);
        for (let y = 0; y < map.height; y++) {
            for (let x = 0; x < map.width; x++) {
                if (cells[y][x] == 'v') {
                    map.put(x, y, 1);
                } else if (cells[y][x] == '>') {
                    map.put(x, y, 2);
                }
            }
        }
        return map;
    }

    private index(x: i32, y: i32): i32 {
        return (y % this.height) * this.width + (x % this.width);
    }

    get(x: i32, y: i32): i8 {
        return this.buffer[this.index(x, y)];
    }

    put(x: i32, y: i32, v: i8): void {
        this.buffer[this.index(x, y)] = v;
    }

    move(): bool {
        let moved = false;
        for (let y = 0; y < this.height; y++) {
            for (let x = 0; x < this.width; x++) {
                if (this.get(x, y) == 2 && this.get(x + 1, y) == 0) {
                    this.put(x, y, x == 0 ? 3 : 0);
                    this.put(x + 1, y, 2);
                    x++;
                    moved = true;
                }
            }
        }
        for (let y = 0; y < this.height; y++) {
            if (this.get(0, y) == 3) {
                this.put(0, y, 0);
            }
        }
        for (let x = 0; x < this.width; x++) {
            for (let y = 0; y < this.height; y++) {
                if (this.get(x, y) == 1 && this.get(x, y + 1) == 0) {
                    this.put(x, y, y == 0 ? 3 : 0);
                    this.put(x, y + 1, 1);
                    y++;
                    moved = true;
                }
            }
        }
        for (let x = 0; x < this.width; x++) {
            if (this.get(x, 0) == 3) {
                this.put(x, 0, 0);
            }
        }
        return moved;
    }
}

export function countSteps(input: string): i32 {
    const map = Map.fromString(input);
    let steps = 1;
    while (map.move()) {
        steps++;
    }
    return steps;
}

