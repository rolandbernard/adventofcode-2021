
import sys
import numpy as np

def parseScanner(s: str):
    split = s.split('\n')
    bacons = [tuple(int(v) for v in b.split(',')) for b in split[1:]]
    return bacons

scanners = [parseScanner(s) for s in sys.stdin.read().strip().split('\n\n')]

def rotate(d, a):
    sin = [0, 1, 0, -1, 0]
    mat = [[1, 0, 0], [0, sin[d + 1], -sin[d]], [0, sin[d], sin[d + 1]]]
    return np.roll(mat, a, (0, 1))

def posibleRotations():
    for y in range(4):
        for x in range(4):
            yield np.dot(rotate(x, 0), rotate(y, 1))
    for z in [1, 3]:
        for x in range(4):
            yield np.dot(rotate(x, 0), rotate(z, 2))

def detectOverlap(a, b):
    for rot in posibleRotations():
        rotateb = [tuple(np.dot(rot, p)) for p in b]
        for i in a:
            for j in rotateb:
                pos = (i[0] - j[0], i[1] - j[1], i[2] - j[2])
                movedb = [(x + pos[0], y + pos[1], z + pos[2]) for x, y, z in rotateb]
                seta = set(a)
                setb = set(movedb)
                if len(seta & setb) >= 12:
                    return (True, pos, rot)
    return (False, None, None)

def applyTransform(trans, rot, point):
    rotated = np.dot(rot, point)
    return (rotated[0] + trans[0], rotated[1] + trans[1], rotated[2] + trans[2])

points = set(scanners[0])
positions = {0: (0, 0, 0)}
missing = set(range(1, len(scanners)))

while len(missing) != 0:
    for k, p in positions.copy().items():
        for i in missing.copy():
            ovl, pos, rot = detectOverlap(scanners[k], scanners[i])
            if ovl:
                apos = (p[0] + pos[0], p[1] + pos[1], p[2] + pos[2])
                points.update(applyTransform(apos, rot, p) for p in scanners[i])
                missing.remove(i)
                positions[i] = apos
                scanners[i] = [tuple(np.dot(rot, p)) for p in scanners[i]]

maxd = max(abs(np.subtract(x, y)).sum() for x in positions.values() for y in positions.values())

print("Result:", maxd)

