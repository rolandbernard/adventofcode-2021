
import sys
import numpy as np

raw = sys.stdin.read()
map = np.array([[c for c in l] for l in raw.split('\n') if len(l) != 0], dtype=int)

def energize(map, i, j):
    if i >= 0 and j >= 0 and i < map.shape[0] and j < map.shape[1] and map[i, j] < 10:
        map[i, j] += 1
        if map[i, j] >= 10:
            for di, dj in [(di, dj) for di in range(-1, 2) for dj in range(-1, 2) if di != 0 or dj != 0]:
                energize(map, i + di, j + dj)

flashes = 0

for _ in range(100):
    for i in range(map.shape[0]):
        for j in range(map.shape[1]):
            energize(map, i, j)
    flashes += (map >= 10).sum()
    map[map >= 10] = 0

print('Result:', flashes)

