
import sys
import numpy as np

from scipy.ndimage import convolve

rawalgo, rawimg = sys.stdin.read().strip().split('\n\n')

algo = np.array([1 if c == '#' else 0 for c in rawalgo])
img = np.array([[1 if c == '#' else 0 for c in line] for line in rawimg.split('\n')])

bin = 2**np.arange(9).reshape(3, 3)

def enhance(img, algo):
    img = np.pad(img, 1, 'edge')
    return algo[convolve(img, bin)]

img = np.pad(img, 1)
for _ in range(50):
    img = enhance(img, algo)

print("Result:", img.sum())

