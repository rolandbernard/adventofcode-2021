
import sys
import json

from functools import reduce

def flatten(number, d = 0):
    if isinstance(number, list):
        return flatten(number[0], d + 1) + flatten(number[1], d + 1)
    else:
        return [(number, d)]

numbers = [flatten(json.loads(s)) for s in sys.stdin.read().strip().split('\n')]

def expode(number):
    for i, (_, d) in enumerate(number):
        if d > 4:
            new = number[:i] + number[i + 1:]
            if i > 0:
                new[i - 1] = (new[i - 1][0] + number[i][0], new[i - 1][1])
            if i < len(new) - 1:
                new[i + 1] = (new[i + 1][0] + number[i + 1][0], new[i + 1][1])
            new[i] = (0, d - 1)
            return True, new
    return False, number

def split(number):
    for i, (n, d) in enumerate(number):
        if n >= 10:
            return True, number[:i] + [(n // 2, d + 1), ((n + 1) // 2, d + 1)] + number[i + 1:]
    return False, number

def normalize(number):
    while True:
        change, number = expode(number)
        if change:
            continue
        change, number = split(number)
        if not change:
            break
    return number

def add(a, b):
    return normalize([(x, d + 1) for x, d in a + b])

def magnitude(number):
    stack = []
    for v in number:
        stack.append(v)
        while len(stack) >= 2 and stack[-1][1] == stack[-2][1]:
            stack[-2] = (3 * stack[-2][0] + 2 * stack[-1][0], stack[-1][1] - 1)
            stack.pop()
    return stack[-1][0]

print('Result:', max(magnitude(add(x, y)) for x in numbers for y in numbers if x != y))

