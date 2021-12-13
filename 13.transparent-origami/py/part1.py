
import sys

raw = sys.stdin.read()

rawpoints, rawfolds = raw.split('\n\n')

points = set((int(p.split(',')[0]), int(p.split(',')[1])) for p in rawpoints.split('\n'))
folds = [ (f.split('=')[0][-1], int(f.split('=')[1])) for f in rawfolds.strip().split('\n') ]

def applyFold(points, fold):
    if fold[0] == 'x':
        return set((x, y) if x < fold[1] else (2 * fold[1] - x, y) for x, y in points)
    elif fold[0] == 'y':
        return set((x, y) if y < fold[1] else (x, 2 * fold[1] - y) for x, y in points)

print("Result:", len(applyFold(points, folds[0])))

