
import sys
import numpy as np

raw = sys.stdin.read()

state, rawinstructions = raw.split('\n\n')
instructions = {}

for inst in rawinstructions.split('\n'):
    split = inst.split('->')
    if len(split) >= 2:
        instructions[split[0].strip()] = split[1].strip()

def expand(state, instructions):
    results = []
    for i in range(len(state)):
        results.append(state[i])
        if state[i:i+2] in instructions:
            results.append(instructions[state[i:i+2]])
    return ''.join(results)

for _ in range(10):
    state = expand(state, instructions)

_, counts = np.unique([c for c in state], return_counts=True)

print("Result:", max(counts) - min(counts))

