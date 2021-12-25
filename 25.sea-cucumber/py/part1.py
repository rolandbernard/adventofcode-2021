
import sys
import numpy as np

map = np.array([[1 if c == 'v' else 2 if c == '>' else 0 for c in l] for l in sys.stdin.read().strip().split('\n')])

def move(map):
    east = (map == 2) & np.roll(map == 0, -1, 1)
    map[east] = 0
    map[np.roll(east, 1, 1)] = 2
    south = (map == 1) & np.roll(map == 0, -1, 0)
    map[south] = 0
    map[np.roll(south, 1, 0)] = 1
    return east.any() or south.any()

steps = 1
while move(map):
    steps += 1

print("Result:", steps)

