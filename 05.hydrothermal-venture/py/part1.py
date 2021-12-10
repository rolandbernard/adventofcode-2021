
import sys
import numpy as np

raw = sys.stdin.read()

lines = [[[int(v) for v in p.split(',')] for p in l.split(' -> ')] for l in raw.split('\n') if len(l) > 0]
lines = [((l[0][0], l[1][0]), (l[0][1], l[1][1])) for l in lines]

width = 1 + max([max(l[0][0], l[1][0]) for l in lines])
height = 1 + max([max(l[0][1], l[1][1]) for l in lines])

map = np.zeros((width, height), dtype=int)

for l in lines:
    if l[0][0] == l[0][1]:
        map[l[0][0], min(l[1]):1 + max(l[1])] += 1
    elif l[1][0] == l[1][1]:
        map[min(l[0]):1 + max(l[0]), l[1][0]] += 1

print('Result:', (map >= 2).sum())

