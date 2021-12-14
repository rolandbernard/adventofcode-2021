
import sys

from collections import defaultdict

raw = sys.stdin.read()
rawstate, rawinstructions = raw.split('\n\n')

state = defaultdict(lambda : 0)
for i in range(len(rawstate) - 1):
    state[rawstate[i:i+2]] += 1

instructions = {}
for inst in rawinstructions.split('\n'):
    split = inst.split('->')
    if len(split) >= 2:
        instructions[split[0].strip()] = split[1].strip()

def expand(state, instructions):
    newstate = defaultdict(lambda : 0)
    for key in state:
        if key in instructions:
            newstate[key[0] + instructions[key]] += state[key]
            newstate[instructions[key] + key[1]] += state[key]
        else:
            newstate[key] += state[key]
    return newstate

for _ in range(40):
    state = expand(state, instructions)

counts = defaultdict(lambda : 0)
counts[rawstate[0]] = 1
counts[rawstate[-1]] = 1
for key in state:
    for c in key:
        counts[c] += state[key]

print('Result:', (max(counts.values()) - min(counts.values())) // 2)

