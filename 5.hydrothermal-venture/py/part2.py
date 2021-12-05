
import sys
import numpy as np

raw = sys.stdin.read()

lines = [[[int(v) for v in p.split(',')] for p in l.split(' -> ')] for l in raw.split('\n') if len(l) > 0]
lines = [((l[0][0], l[1][0]), (l[0][1], l[1][1])) for l in lines]

width = 1 + max([max(l[0][0], l[1][0]) for l in lines])
height = 1 + max([max(l[0][1], l[1][1]) for l in lines])

map = np.zeros((width, height), dtype=int)

for l in lines:
    dx = 1 if l[0][1] > l[0][0] else -1
    dy = 1 if l[1][1] > l[1][0] else -1
    map[range(l[0][0], dx + l[0][1], dx), range(l[1][0], dy + l[1][1], dy)] += 1

print('Result:', (map >= 2).sum())

