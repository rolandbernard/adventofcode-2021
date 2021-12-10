
import sys
import numpy as np

raw = sys.stdin.read()
locs = np.fromstring(raw, dtype=np.int64, sep=',')

average = np.average(locs)

def forLocation(locs, dest):
    absolute = np.abs(locs - dest)
    return ((absolute + 1) * absolute // 2).sum()

print('Result:', min(
    forLocation(locs, int(np.ceil(average))),
    forLocation(locs, int(np.floor(average)))
))

