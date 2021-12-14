
const fs = require('fs');

const raw = fs.readFileSync(process.stdin.fd).toString();

const map = {};
for (const l of raw.split('\n').filter(l => l)) {
    [a, b] = l.trim().split('-');
    map[a] = map[a] ?? [];
    map[a].push(b);
    map[b] = map[b] ?? [];
    map[b].push(a);
}

function countPaths(map, allow = true, seen = {}, at = 'start') {
    if (at === 'end') {
        return 1
    } else if (at.toLowerCase() === at && seen[at]) {
        if (allow && at !== 'start') {
            return (map[at] ?? [])
                .map(c => countPaths(map, false, {...seen, [at]: true}, c))
                .reduce((a, b) => a + b, 0);
        } else {
            return 0
        }
    } else {
        return (map[at] ?? [])
            .map(c => countPaths(map, allow, {...seen, [at]: true}, c))
            .reduce((a, b) => a + b, 0);
    }
}

console.log("Result:", countPaths(map))

