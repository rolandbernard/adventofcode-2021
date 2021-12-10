
import sys
import numpy as np

raw = sys.stdin.read()
map = np.array([[c for c in l] for l in raw.split('\n') if len(l) != 0], dtype=int)
map = np.pad(map, 1, constant_values = 9)

def measureBasin(i: int, j: int):
    surveyed = set()
    to_survey = [(i, j)]
    while len(to_survey) != 0:
        p = to_survey.pop()
        if map[p] != 9 and p not in surveyed:
            surveyed.add(p)
            to_survey.append((p[0] - 1, p[1]))
            to_survey.append((p[0] + 1, p[1]))
            to_survey.append((p[0], p[1] - 1))
            to_survey.append((p[0], p[1] + 1))
    return len(surveyed)

sizes = []
for i in range(1, map.shape[0] - 1):
    for j in range(1, map.shape[1] - 1):
        if map[(i - 1, i + 1, i, i), (j, j, j + 1, j - 1)].min() > map[i, j]:
            sizes.append(measureBasin(i, j))
sizes = sorted(sizes)

print('Result:', sizes[-1] * sizes[-2] * sizes[-3])

