
import { readFileSync } from 'fs';

const text = readFileSync(process.stdin.fd).toString()
const numbers = text.split(',').filter(v => v).map(v => parseInt(v))

const state = new BigInt64Array(9);
for (const n of numbers) {
    state[n]++;
}

for (let i = 0; i < 256; i++) {
    const births = state[0];
    for (let i = 1; i < 9; i++) {
        state[i - 1] = state[i];
    }
    state[6] += births;
    state[8] = births;
}

console.log('Result:', state.reduce((a, b) => a + b));

