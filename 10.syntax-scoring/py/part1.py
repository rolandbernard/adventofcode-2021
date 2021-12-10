
import sys

count = 0

for line in sys.stdin:
    stack = []
    for c in line.strip():
        if c in {'(', '[', '{', '<'}:
            stack.append(c)
        elif stack[-1] == {')': '(', ']': '[', '}': '{', '>': '<'}[c]:
            stack.pop()
        else:
            count += {')': 3, ']': 57, '}': 1197, '>': 25137}[c]
            break

print("Result:", count)

