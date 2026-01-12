import argparse


parser = argparse.ArgumentParser(prog='pascal_triangle')
parser.add_argument('number')
args = parser.parse_args()
n = int(args.number)


trg_h = 10
trg_pas = []
for i in range(trg_h):
    row = [1] * (i + 1)
    for j in range(i + 1):
        if (j != 0 and j != i):
            row[j] = trg_pas[i - 1][j - 1] + trg_pas[i - 1][j]
    trg_pas.append(row)


for i in range(n):
    for j in range(n - i):
        print(' ', end = '')
    for j in range(i + 1):
        print(trg_pas[i][j], ' ', end = '')
    print()