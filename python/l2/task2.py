#1
s = input()
f = 'True'
for i in range(len(s)):
    if (s[i] != s[-i - 1]):
        f = 'False'
        break
print(f)


#2
print()
s = "Hello world 123 345 8 qwertyuiop"
lst = s.split(' ')
max_len = 0
for i in lst:
    if (max_len < max(len(i), max_len)):
        max_len = len(i)
        max_w = i
print(max_w, max_len)


#3
import random


print()
n = 10
num_list = [random.randint(1, 10000) for i in range(n)]
n_ev = 0
n_nev = 0
for i in num_list:
    if i % 2 == 0:
        n_ev += 1
    else:
        n_nev += 1
print(num_list)
print('even: {}, not even: {}'.format(n_ev, n_nev))


#4
print()
words = {'water':'aqua', 'soil':'earth', 'light':'bright'}
sent = "water soil light"
lst = sent.split(' ')
for i in range(len(lst)):
    syn = words.get(lst[i])
    if syn != None:
        lst[i] = syn
print(' '.join(lst))


#5
print()
def fib(num:int) -> int:
    if num < 2:
        return num
    return fib(num - 1) + fib(num - 2)

n = int(input())
print(fib(n))


#6
print()
import string


with open('python/input.txt') as f:
    str_lst = f.readlines()
    print('str count: ', len(str_lst))


    wrd_cnt = 0
    for str in str_lst:
        wrd_lst = str.split(' ')
        for wrd in wrd_lst:
            if len(wrd) == 1 and wrd.isalpha():
                wrd_cnt += 1
            elif len(wrd) > 1:
                wrd_cnt += 1
                
    print('words count: ', wrd_cnt)

    
    lst = []
    for str in str_lst:
        lst.extend(str.split('\n'))
    print('symb count: ', len(''.join(lst)))

#7
print()
def fun_iter(b, q):
    s = b
    while True:
        yield s
        s = s * q


import time


fit = fun_iter(3, 2)
while True:
    print(next(fit))
    time.sleep(1)