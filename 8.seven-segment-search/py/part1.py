
import sys

count = 0

for line in sys.stdin:
    _, number = [v.strip().split(' ') for v in line.split(' | ')]
    count += sum([len(n) in [2, 3, 4, 7] for n in number])

print('Result:', count)

