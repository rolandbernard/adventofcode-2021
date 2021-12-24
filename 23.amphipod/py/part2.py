
import sys
import heapq as hq

raw = sys.stdin.read()
map = [[c for c in l.strip().split('#') if len(c) != 0] for l in raw.split('\n')[2:4]]
map = [map[0], ['D', 'C', 'B', 'A'], ['D', 'B', 'A', 'C'], map[1]]
pos = [[], [], [], []]
for i in range(4):
    for j in range(4):
        pos[ord(map[i][j]) - ord('A')].append((2 + j*2, -1-i))

def finished(s):
    for i in range(4):
        for j in range(4):
            if s[j][i][1] >= 0 or s[j][i][0] != 2 + 2*j:
                return False
    return True

def heur(s):
    h = 0
    for i, l in enumerate(s):
        for x in l:
            if x[0] == 0:
                h += 10**i * (abs(x[0] - (2+2*i)) + 1)
            elif x[0] != (2+2*i):
                h += 10**i * (abs(x[0] - (2+2*i)) + -x[1] + 1)
    return h

def canMoveTo(s, f, d):
    return (
        (d[1] != 0 or d[0] not in {2, 4, 6, 8})
        and all((
            (x[1] != 0 or x[0] <= min(f[0], d[0]) or x[0] >= max(f[0], d[0]))
            and (x[0] != d[0] or x[1] < d[1])
            and (x[0] != f[0] or x[1] < f[1])
            and (d[1] == 0 or x[0] != d[0] or x[0] == 2+2*i)
            for i, l in enumerate(s) for x in l
            if x != f
        ))
    )

def toList(s):
    return list(list(i) for i in s)

def toTuple(s):
    return tuple(tuple(sorted(i)) for i in s)

result = pos
pos = toTuple(pos)
cost = {pos: 0}
queue = [(heur(pos), 0, pos)]
while queue:
    h, d, s = hq.heappop(queue)
    if cost[s] < d:
        continue
    if finished(s):
        result = s
        break
    for i in range(4):
        for j in range(4):
            if s[j][i][1] == 0:
                for h in [-1, -2, -3, -4]:
                    if canMoveTo(s, s[j][i], (2+2*j, h)):
                        pos = toList(s)
                        pos[j][i] = (2+2*j, h)
                        c = d + 10**j * (abs(pos[j][i][0] - s[j][i][0]) + abs(pos[j][i][1] - s[j][i][1]))
                        pos = toTuple(pos)
                        if pos not in cost or cost[pos] > c:
                            cost[pos] = c
                            hq.heappush(queue, (c + heur(pos), c, pos))
            else:
                for h in range(11):
                    if canMoveTo(s, s[j][i], (h, 0)):
                        pos = toList(s)
                        pos[j][i] = (h, 0)
                        c = d + 10**j * (abs(pos[j][i][0] - s[j][i][0]) + abs(pos[j][i][1] - s[j][i][1]))
                        pos = toTuple(pos)
                        if pos not in cost or cost[pos] > c:
                            cost[pos] = c
                            hq.heappush(queue, (c + heur(pos), c, pos))

print('Result:', cost[result])

