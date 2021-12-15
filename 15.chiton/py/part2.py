
import sys
import numpy as np
import heapq as hq

raw = sys.stdin.read()
map = np.array([[c for c in l] for l in raw.split('\n') if len(l) != 0], dtype=int)
map = np.concatenate([ map + i for i in range(5) ], 0)
map = np.concatenate([ map + i for i in range(5) ], 1)
map = (map - 1) % 9 + 1
dist = np.full((map.shape[0], map.shape[1]), 10000000)

dist[0, 0] = 0
queue = [(0, 0, 0)]
while queue:
    _, x, y = hq.heappop(queue)
    if x == dist.shape[0] and y == dist.shape[1]:
        break
    if x != 0 and dist[x, y] + map[x - 1, y] < dist[x - 1, y]:
        dist[x - 1][y] = dist[x][y] + map[x - 1, y]
        hq.heappush(queue, (dist[x - 1][y], x - 1, y))
    if y != 0 and dist[x, y] + map[x, y - 1] < dist[x, y - 1]:
        dist[x][y - 1] = dist[x][y] + map[x, y - 1]
        hq.heappush(queue, (dist[x][y - 1], x, y - 1))
    if x != dist.shape[0] - 1 and dist[x, y] + map[x + 1, y] < dist[x + 1, y]:
        dist[x + 1][y] = dist[x][y] + map[x + 1, y]
        hq.heappush(queue, (dist[x + 1][y], x + 1, y))
    if y != dist.shape[1] - 1 and dist[x, y] + map[x, y + 1] < dist[x, y + 1]:
        dist[x][y + 1] = dist[x][y] + map[x, y + 1]
        hq.heappush(queue, (dist[x][y + 1], x, y + 1))

print('Result:', dist[-1, -1])

