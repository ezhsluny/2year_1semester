import argparse
import random


parser = argparse.ArgumentParser(prog='bubble_sort')
parser.add_argument('number')
args = parser.parse_args()
n = int(args.number)


list = []
for i in range(0, n):
    list.append(random.random())


tmp = 0
for i in range(0, n):
    for j in range(n - 1, i, -1):
        if list[j] < list[j - 1]:
            tmp = list[j]
            list[j] = list[j - 1]
            list[j - 1] = tmp

for i in range(0, n):
    print(list[i])