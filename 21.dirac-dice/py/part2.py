
import sys

from collections import defaultdict
from functools import cache

pos = tuple(int(l[-1]) for l in sys.stdin.read().strip().split('\n'))

prob = defaultdict(lambda: 0)
for i in range(1, 4):
    for j in range(1, 4):
        for k in range(1, 4):
            prob[i + j + k] += 1

def applyStep(pos, points, player, d):
    p = (pos[player] + d - 1) % 10 + 1
    if player == 0:
        return (p, pos[1]), (points[0] + p, points[1]), 1 - player
    else:
        return (pos[0], p), (points[0], points[1] + p), 1 - player

@cache
def universes(pos, points = (0, 0), player = 0):
    if max(points) >= 21:
        return (1, 0) if points[0] > points[1] else (0, 1)
    else:
        res = [0, 0]
        for d, n in prob.items():
            w0, w1 = universes(*applyStep(pos, points, player, d))
            res[0] += n * w0
            res[1] += n * w1
        return tuple(res)

print("Result:", max(universes(pos)))

