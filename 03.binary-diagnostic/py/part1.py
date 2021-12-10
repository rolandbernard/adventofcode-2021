
import fileinput

size = 0
count = [0] * 12

for line in fileinput.input():
    size += 1
    for i in range(12):
        if line[i] == '1':
            count[i] += 2

most = int(''.join(['1' if v > size else '0' for v in count]), 2)
least = int(''.join(['1' if v <= size else '0' for v in count]), 2)

print('Solution:', most * least)

