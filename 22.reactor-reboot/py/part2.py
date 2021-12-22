
import sys

seq = []
for line in sys.stdin.read().strip().split('\n'):
    on, pos = line.split(' ')
    iv = tuple(tuple(int(v) for v in l.split('=')[1].split('..')) for l in line.split(','))
    seq.append((on == 'on', iv))

def splitIntersection(i0, i1):
    xs, ys, zs = [sorted(i0[i] + i1[i]) for i in range(3)]
    splits = [
        ((xs[1], xs[2]), (ys[1], ys[2]), (zs[2] + 1, i1[2][1])),
        ((xs[1], xs[2]), (ys[1], ys[2]), (i1[2][0], zs[1] - 1)),
        ((xs[1], xs[2]), (i1[1][0], ys[1] - 1), i1[2]),
        ((xs[1], xs[2]), (ys[2] + 1, i1[1][1]), i1[2]),
        ((i1[0][0], xs[1] - 1), i1[1], i1[2]),
        ((xs[2] + 1, i1[0][1]), i1[1], i1[2]),
    ]
    return filter(lambda v: v[0][1] >= v[0][0] and v[1][1] >= v[1][0] and v[2][1] >= v[2][0], splits)

reactor = set()

for on, iv in seq:
    overlaps = []
    for i in reactor:
        if (
            iv[0][0] <= i[0][1] and iv[0][1] >= i[0][0]
            and iv[1][0] <= i[1][1] and iv[1][1] >= i[1][0]
            and iv[2][0] <= i[2][1] and iv[2][1] >= i[2][0]
        ):
            overlaps.append(i)
    reactor.difference_update(overlaps)
    for ov in overlaps:
        reactor.update(splitIntersection(iv, ov))
    if on:
        reactor.add(iv)

count = sum(map(lambda i: (i[0][1] - i[0][0] + 1) * (i[1][1] - i[1][0] + 1) * (i[2][1] - i[2][0] + 1), reactor))

print("Result:",  count)

