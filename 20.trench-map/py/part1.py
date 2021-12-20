
import sys
import numpy as np

rawalgo, rawimg = sys.stdin.read().strip().split('\n\n')

algo = np.array([1 if c == '#' else 0 for c in rawalgo], dtype=np.int8)
img = np.array([[1 if c == '#' else 0 for c in line] for line in rawimg.split('\n')], dtype=np.int8)

def enhance(img, algo):
    img = np.pad(img, 3, 'edge')
    new = np.copy(img)
    for i in range(1, img.shape[0] - 1):
        for j in range(1, img.shape[1] - 1):
            values = img[i-1:i+2,j-1:j+2].flatten()
            index = values.dot(2**np.arange(values.size)[::-1])
            new[i,j] = algo[index]
    return new[1:-1,1:-1]

img = np.pad(img, 1)
for _ in range(2):
    img = enhance(img, algo)

print("Result:", img.sum())

