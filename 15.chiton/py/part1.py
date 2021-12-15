
import sys
import numpy as np

raw = sys.stdin.read()
map = np.array([[c for c in l] for l in raw.split('\n') if len(l) != 0], dtype=int)
dist = np.full(map.shape, 10000000)

dist[0, 0] = 0
queue = [(0, 0)]
for x, y in queue:
    if x != 0 and dist[x, y] + map[x - 1, y] < dist[x - 1, y]:
        dist[x - 1][y] = dist[x][y] + map[x - 1, y]
        queue.append((x - 1, y))
    if y != 0 and dist[x, y] + map[x, y - 1] < dist[x, y - 1]:
        dist[x][y - 1] = dist[x][y] + map[x, y - 1]
        queue.append((x, y - 1))
    if x != dist.shape[0] - 1 and dist[x, y] + map[x + 1, y] < dist[x + 1, y]:
        dist[x + 1][y] = dist[x][y] + map[x + 1, y]
        queue.append((x + 1, y))
    if y != dist.shape[1] - 1 and dist[x, y] + map[x, y + 1] < dist[x, y + 1]:
        dist[x][y + 1] = dist[x][y] + map[x, y + 1]
        queue.append((x, y + 1))

print('Result:', dist[-1, -1])

