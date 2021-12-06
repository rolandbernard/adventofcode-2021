
import sys
import numpy as np

raw = sys.stdin.read()
x = np.zeros(10, dtype=np.int64)

for v in raw.split(','):
    x[int(v)] += 1

m = np.zeros((10, 10), dtype=np.int64)
m[(6, 8), 0] = 1
for i in range(1, 10):
    m[i - 1, i] = 1
m = np.linalg.matrix_power(m, 80)

x = np.matmul(m, x)
print('Result:', x.sum())

