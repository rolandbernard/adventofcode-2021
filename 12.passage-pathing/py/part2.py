
import sys

from collections import defaultdict

map = defaultdict(lambda : set())

for l in sys.stdin:
    a, b = l.strip().split('-')
    map[a].add(b)
    map[b].add(a)

def countPaths(map, allow = True, seen = set(), at = 'start'):
    if at == 'end':
        return 1
    elif at.islower() and at in seen:
        if allow and at != 'start':
            return sum(countPaths(map, False, seen | { at }, con) for con in map[at])
        else:
            return 0
    else:
        return sum(countPaths(map, allow, seen | { at }, con) for con in map[at])

print("Result:", countPaths(map))

