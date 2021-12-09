
import sys
import numpy as np

raw = sys.stdin.read()
map = np.array([[c for c in l] for l in raw.split('\n') if len(l) != 0], dtype=int)

padded = np.pad(map, 1, constant_values = 9)
ad = np.dstack([ np.roll(padded, i, axis=j) for i, j in [(x, y) for x in [1, -1] for y in [0, 1]] ])
min = ad.min(2)[1:-1,1:-1]

print('Result:', (map[min > map] + 1).sum())

