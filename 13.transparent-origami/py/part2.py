
import sys

from functools import reduce

raw = sys.stdin.read()

rawpoints, rawfolds = raw.split('\n\n')

points = set((int(p.split(',')[0]), int(p.split(',')[1])) for p in rawpoints.split('\n'))
folds = [ (f.split('=')[0][-1], int(f.split('=')[1])) for f in rawfolds.strip().split('\n') ]

def applyFold(points, fold):
    if fold[0] == 'x':
        return set((x, y) if x < fold[1] else (2 * fold[1] - x, y) for x, y in points)
    elif fold[0] == 'y':
        return set((x, y) if y < fold[1] else (x, 2 * fold[1] - y) for x, y in points)

for fold in folds:
    points = applyFold(points, fold)

min = reduce(lambda a, x: (min(a[0], x[0]), min(a[1], x[1])), points)
max = reduce(lambda a, x: (max(a[0], x[0]), max(a[1], x[1])), points)

print('Result:')

for y in range(min[1], max[1] + 1):
    for x in range(min[0], max[0] + 1):
        print('██' if (x, y) in points else '  ', end='')
    print()

