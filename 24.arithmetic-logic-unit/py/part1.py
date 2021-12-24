
import sys

from z3 import *

raw = sys.stdin.read()
instr = [l.split(' ') for l in raw.strip().split('\n')]

inp = []
bits = 32
regs = {
    'w': BitVecVal(0, bits), 'x': BitVecVal(0, bits), 'y': BitVecVal(0, bits), 'z': BitVecVal(0, bits),
}

for i in instr:
    if i[0] == 'inp':
        inp.append(BitVec('i' + str(len(inp)), bits))
        regs[i[1]] = inp[-1]
    elif i[0] == 'add':
        regs[i[1]] = regs[i[1]] + (
           regs[i[2]] if i[2].isalpha() else int(i[2])
        )
    elif i[0] == 'mul':
        if i[2] == '0' or regs[i[1]] == 0:
            regs[i[1]] = 0
        else:
            regs[i[1]] = regs[i[1]] * (
               regs[i[2]] if i[2].isalpha() else int(i[2])
            )
    elif i[0] == 'div':
        regs[i[1]] = regs[i[1]] / (
           regs[i[2]] if i[2].isalpha() else int(i[2])
        )
    elif i[0] == 'mod':
        regs[i[1]] = regs[i[1]] % (
           regs[i[2]] if i[2].isalpha() else int(i[2])
        )
    elif i[0] == 'eql':
        regs[i[1]] = If(regs[i[1]] == (
           regs[i[2]] if i[2].isalpha() else int(i[2])
        ), BitVecVal(1, bits), BitVecVal(0, bits))

o = Optimize()
for i in inp:
    o.add(i <= 9)
    o.add(i >= 1)
o.add(regs['z'] == 0)
val = BitVecVal(0, 48)
for i in inp:
    val = val * 10 + ZeroExt(48 - bits, i)
number = BitVec('number', 48)
o.add(number == val)

o.maximize(number)
o.check()
m = o.model()

print("Result:", m.eval(number, model_completion=True))

