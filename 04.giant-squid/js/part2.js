
const fs = require('fs');

const text = fs.readFileSync(process.stdin.fd).toString()

const [numraw, ...boaraw] = text.split('\n\n')

const numbers = numraw.split(',').map(v => parseInt(v));
const boards = boaraw.map(
    b => b.split('\n').filter(l => l).map(
        l => l.split(' ').filter(v => v).map(v => parseInt(v))
))

const numbered = numbers.reduce((a, n, i) => (a[n] = i, a), {});

let max_board;
let max_count = -Infinity;

for (const b of boards) {
    const count = Math.min(
        ...b.map(l => Math.max(...l.map(v => numbered[v] ?? Infinity))),
        ...b[0].map((_, i) => Math.max(...b.map(l => numbered[l[i]] ?? Infinity))),
    )
    if (count > max_count) {
        max_count = count;
        max_board = b;
    }
}

const first = max_board.flat()
    .filter(v => (numbered[v] ?? Infinity) > max_count)
    .reduce((a, b) => a + b);
const second = max_board.flat().filter(v => numbered[v] === max_count)[0];

console.log("Parts:", first, second);
console.log("Result:", first * second);

