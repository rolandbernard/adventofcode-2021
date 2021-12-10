
import sys
import numpy as np

raw = sys.stdin.read()
locs = np.fromstring(raw, dtype=np.int64, sep=',')

median = int(np.median(locs))
print('Result:', np.abs(locs - median).sum())

