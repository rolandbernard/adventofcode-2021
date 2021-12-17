
import { readFileSync } from 'fs';

const hex = readFileSync(process.stdin.fd).toString().trim()
const bits = hex.split('').map(x => parseInt(x, 16).toString(2).padStart(4, '0')).join('')
let bits_pos = 0;

function readBits(size: number) {
    bits_pos += size;
    return parseInt(bits.substr(bits_pos - size, size), 2);
}

function readPackets(): number {
    const version = readBits(3);
    const type = readBits(3);
    if (type == 4) {
        while ((readBits(5) & 0x10) != 0);
        return version;
    } else {
        if (readBits(1) == 0) {
            const length = readBits(15);
            const end = bits_pos + length;
            let res = version;
            while (bits_pos < end) {
                res += readPackets();
            }
            return res;
        } else {
            const length = readBits(11);
            let res = version;
            for (let i = 0; i < length; i++) {
                res += readPackets();
            }
            return res;
        }
    }
}

console.log('Result:', readPackets());

