
const fs = require('fs');
const bind = require('as-bind/dist/as-bind.cjs');

const wasm = fs.readFileSync('as/part1.wasm');
const text = fs.readFileSync(process.stdin.fd).toString();

(async () => {
    const inst = await bind.instantiate(wasm);
    console.log('Result:', inst.exports.countSteps(text));
})();

