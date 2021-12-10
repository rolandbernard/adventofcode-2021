
import sys

scores = []
for line in sys.stdin:
    error = False
    stack = []
    for c in line.strip():
        if c in {'(', '[', '{', '<'}:
            stack.append(c)
        elif stack[-1] == {')': '(', ']': '[', '}': '{', '>': '<'}[c]:
            stack.pop()
        else:
            error = True
            break
    value = 0
    if not error:
        while len(stack) != 0:
            value = 5 * value + {'(': 1, '[': 2, '{': 3, '<': 4}[stack.pop()]
        scores.append(value)

print("Result:", sorted(scores)[len(scores) // 2])

