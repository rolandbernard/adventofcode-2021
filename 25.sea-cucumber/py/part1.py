
import sys
import numpy as np

map = np.array([[1 if c == 'v' else 2 if c == '>' else 0 for c in l] for l in sys.stdin.read().strip().split('\n')])

def move(map):
    new = map.copy()
    east = (new == 2) & np.roll(new == 0, -1, 1)
    new[east] = 0
    new[np.roll(east, 1, 1)] = 2
    south = (new == 1) & np.roll(new == 0, -1, 0)
    new[south] = 0
    new[np.roll(south, 1, 0)] = 1
    return new

old = None
steps = 0
while (map != old).any():
    old = map
    map = move(map)
    steps += 1

print("Result:", steps)

