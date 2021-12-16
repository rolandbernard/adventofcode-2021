
import { readFileSync } from 'fs';

const hex = readFileSync(process.stdin.fd).toString().trim()
const bits = hex.split('').map(x => parseInt(x, 16).toString(2).padStart(4, '0')).join('')
let bits_pos = 0;

function readBits(size: number): bigint {
    bits_pos += size;
    return BigInt('0b' + bits.substr(bits_pos - size, size));
}

function readPackets(): bigint {
    readBits(3);
    const type = readBits(3);
    if (type == 4n) {
        let value = 0n;
        let cur = 0n;
        do {
            cur = readBits(5);
            value <<= 4n;
            value |= cur & 0xfn;
        } while ((cur & 0x10n) != 0n);
        return value;
    } else {
        const values: bigint[] = [];
        if (readBits(1) == 0n) {
            const length = Number(readBits(15));
            const end = bits_pos + length;
            while (bits_pos < end) {
                values.push(readPackets());
            }
        } else {
            const length = Number(readBits(11));
            for (let i = 0; i < length; i++) {
                values.push(readPackets());
            }
        }
        switch (Number(type)) {
            case 0:
                return values.reduce((a, b) => a + b);
            case 1:
                return values.reduce((a, b) => a * b);
            case 2:
                return values.reduce((a, b) => a < b ? a : b);
            case 3:
                return values.reduce((a, b) => a > b ? a : b);
            case 5:
                return values[0] > values[1] ? 1n : 0n;
            case 6:
                return values[0] < values[1] ? 1n : 0n;
            case 7:
                return values[0] == values[1] ? 1n : 0n;
            default:
                return 0n;
        }
    }
}

console.log('Result:', readPackets());

