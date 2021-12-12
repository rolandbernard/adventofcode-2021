
import sys

from collections import defaultdict

map = defaultdict(lambda : set())

for l in sys.stdin:
    a, b = l.strip().split('-')
    map[a].add(b)
    map[b].add(a)

def countPaths(map, seen = set(), at = 'start'):
    if at == 'end':
        return 1
    elif at.islower() and at in seen:
        return 0
    else:
        return sum(countPaths(map, seen | { at }, con) for con in map[at])

print("Result:", countPaths(map))

