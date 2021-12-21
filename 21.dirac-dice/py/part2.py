
import sys

from collections import defaultdict

pos = [int(l[-1]) for l in sys.stdin.read().strip().split('\n')]

prob = defaultdict(lambda: 0)
for i in range(1, 4):
    for j in range(1, 4):
        for k in range(1, 4):
            prob[i + j + k] += 1

def applyStep(points, player):
    new = defaultdict(lambda: 0)
    change = False
    for p, v in points.items():
        if max(p[0], p[1]) < 21:
            change = True
            for d, n in prob.items():
                if player == 0:
                    pos = (p[2] + d - 1) % 10 + 1
                    new[(p[0] + pos, p[1], pos, p[3])] += v * n
                else:
                    pos = (p[3] + d - 1) % 10 + 1
                    new[(p[0], p[1] + pos, p[2], pos)] += v * n
        else:
            new[p] += v
    return change, new

points = {(0, 0, pos[0], pos[1]): 1}
step = 0
change = True
while change:
    change, points = applyStep(points, step % 2)
    step += 1

win0 = sum(n if p[0] > p[1] else 0 for p, n in points.items())
win1 = sum(n if p[1] > p[0] else 0 for p, n in points.items())

print("Result:", max(win0, win1))

