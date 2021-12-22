
import sys
import numpy as np

seq = []
for line in sys.stdin.read().strip().split('\n'):
    on, pos = line.split(' ')
    x, y, z = [[int(v) + 50 for v in l.split('=')[1].split('..')] for l in line.split(',')]
    if max(*x, *y, *z) <= 100 and min(*x, *y, *z) >= 0:
        seq.append([on == 'on', x, y, z])

reactor = np.zeros((101, 101, 101), dtype=np.bool8)

for s in seq:
    reactor[s[1][0]:s[1][1]+1,s[2][0]:s[2][1]+1,s[3][0]:s[3][1]+1] = s[0]

print("Result:", reactor.sum())

