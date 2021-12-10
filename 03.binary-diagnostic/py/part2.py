
import fileinput

most = []
least = []

for line in fileinput.input():
    most.append(line.strip())
    least.append(line.strip())

def countCommon(values, i):
    ones = sum([2 * int(v[i]) for v in values])
    if ones < len(values):
        return ('0', '1')
    else:
        return ('1', '0')

for i in range(12):
    if len(most) != 1:
        common = countCommon(most, i)
        most = [v for v in most if v[i] == common[0]]
    if len(least) != 1:
        common = countCommon(least, i)
        least = [v for v in least if v[i] == common[1]]

print('Solution:', int(most[0], 2) * int(least[0], 2))

