
import sys

pos = [int(l[-1]) for l in sys.stdin.read().strip().split('\n')]

def dice():
    while True:
        for i in range(1, 101):
            yield i

gen = dice()
steps = 0
points = [0, 0]
while max(points) < 1000:
    i = steps % 2
    pos[i] += next(gen) + next(gen) + next(gen)
    pos[i] = (pos[i] - 1) % 10 + 1
    points[i] += pos[i]
    steps += 1

print("Result:", 3 * steps * min(points))

