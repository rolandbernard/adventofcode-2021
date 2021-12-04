
import sys
import numpy as np

raw = sys.stdin.read()

numraw, boaraw = raw.split('\n\n', 1)

numbers = np.fromstring(numraw, dtype=int, sep=',')
boards = np.fromstring(boaraw, dtype=int, sep=' ').reshape(-1, 5, 5)

for n in numbers:
    boards[boards == n] = -1
    called = boards == -1
    winners = (called.all(1) | called.all(2)).any(1)
    if winners.any():
        boards[boards == -1] = 0
        print('Solution:', boards[winners].sum() * n)
        exit()

