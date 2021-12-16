
import sys
import numpy as np

bits = bin(int(sys.stdin.read(), 16))[2:]

def readBits(size):
    global bits
    value = int(bits[:size], 2)
    bits = bits[size:]
    return value

def readPackets():
    _ = readBits(3)
    type = readBits(3)
    if type == 4:
        part = readBits(5)
        value = part & 0xf
        while (part & 0x10) != 0:
            part = readBits(5)
            value <<= 4
            value |= part & 0xf
        return value
    else:
        values = []
        if readBits(1) == 0:
            length = readBits(15)
            end = len(bits) - length
            while len(bits) > end:
                values.append(readPackets())
        else:
            length = readBits(11)
            for _ in range(length):
                values.append(readPackets())
        if type == 0:
            return sum(values)
        elif type == 1:
            return np.prod(values)
        elif type == 2:
            return min(values)
        elif type == 3:
            return max(values)
        elif type == 5:
            return 1 if values[0] > values[1] else 0
        elif type == 6:
            return 1 if values[0] < values[1] else 0
        elif type == 7:
            return 1 if values[0] == values[1] else 0

print("Result:", readPackets())

