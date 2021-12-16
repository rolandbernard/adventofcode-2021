
import sys

bits = bin(int(sys.stdin.read(), 16))[2:]

def readBits(size):
    global bits
    value = int(bits[:size], 2)
    bits = bits[size:]
    return value

def readPackets():
    version = readBits(3)
    type = readBits(3)
    if type == 4:
        while (readBits(5) & 0x10) != 0:
            pass
        return version
    else:
        if readBits(1) == 0:
            length = readBits(15)
            end = len(bits) - length
            res = version
            while len(bits) > end:
                res += readPackets()
            return res
        else:
            length = readBits(11)
            return version + sum(readPackets() for _ in range(length))

print("Result:", readPackets())

