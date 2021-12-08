
import sys
import numpy as np

freq_map = {
    42: 0, 17: 1, 34: 2, 39: 3, 30: 4,
    37: 5, 41: 6, 25: 7, 49: 8, 45: 9,
}

count = 0

for line in sys.stdin:
    pattern, number = [v.strip().split(' ') for v in line.split(' | ')]
    _, freq = np.unique([c for p in pattern for c in p], return_counts=True)
    value = 0
    for n in number:
        value *= 10
        value += freq_map[sum([freq[ord(c) - ord('a')] for c in n])]
    count += value

print('Result:', count)

