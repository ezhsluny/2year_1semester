import random

#1
a = random.randint(100, 999)
s = 0
s = (a // 100) + (a % 100 // 10) + (a % 10)
print('1: ', a, s)

#2
a = random.randint(0, 1000000)
print('2: ', a)
s = 0
while (a // 10 != 0):
    b = a % 10
    s += b
    a //= 10
print(s + a)

#3
from math import pi
r = input('радиус сферы: ')
r = int(r)
spov = 4 * r**2 * pi
vsph = 4 / 3 * pi * r**3
print ('площадь пов-ти сферы: ', spov, ', объем: ', vsph)

#4
year = input('year: ')
year = int(year)
if (year % 400 == 0):
    print('visokosny')
elif (year % 100 != 0 and year % 4 == 0):
    print('visokosny')
else:
    print('no')

#5
n = input('n:')
n = int(n)
for i in range (1, n + 1):
    if (i == 1):
        continue
    elif (i == 2 or i == 3):
        print(i)
    else:
        flag = 0
        for d in range(2, i):
            if (i % d == 0):
                flag = 1
                break
        if (flag == 0):
            print(i)

#6
x = input('vklad: ')
x = int(x)
y = input('years: ')
y = int(y)
vklad_end = x
for i in range(1, y + 1):
    vklad_end += 0.1 * vklad_end
print(vklad_end)

#7
import os
path = "./"
tree = os.walk(path)
for i in tree:
    if (i[-1]):
        print(i[-1])







import os
import re
import math as m

def separate_letter(letter: str):
  letter = " ".join(letter)
  letter = re.sub(r'[^a-zA-Z\s]', '', letter)
  letter = re.split(' |\n', letter)
  return letter

path_spam = "/home/ezhsluny/Downloads/enron1/spam"
tree_spam = os.walk(path_spam)
spam_words = set() # Используем set для хранения уникальных слов
file_counts = {} # Используем словарь для подсчета файлов

for walk_res in tree_spam:
  if (walk_res[-1]):
    filenames = walk_res[-1]
    for filename in filenames:
      with open(path_spam + '/' + filename, 'r', encoding="utf-8", errors='ignore') as f:
        spam_text = f.readlines()
        spam_text = separate_letter(spam_text)
        for word in spam_text:
          spam_words.add(word) # Добавляем слова в set
          if word in file_counts:
            file_counts[word] += 1
          else:
            file_counts[word] = 1

print(spam_words)
print(file_counts)

with open('/home/ezhsluny/Documents/TViMS/output.txt', 'w') as f:
  f.write(str(file_counts)) # Выводим словарь с подсчетом файлов

path_legit = "/home/ezhsluny/Downloads/enron1/ham"
tree_legit = os.walk(path_legit)
for legit_walk in tree_legit:
  if legit_walk[-1]:
    legitname = legit_walk[-1]

all_letters_num = len(legitname) + len(filename)

p_spam = m.log1p(len(filename)/all_letters_num)
letter = "/home/ezhsluny/Downloads/enron1/ham/0068.1999-12-27.farmer.ham.txt"
with open(letter, 'r') as l:
  letter_text = l.readlines()
  letter_text = separate_letter(letter_text)
  sum_p_word_spam = 0
  for word in letter_text:
    if word in file_counts:
      sum_p_word_spam += m.log1p((file_counts[word] + 1)/(len(filename) + 2)) # Используем счетчик из словаря
    else:
      sum_p_word_spam += m.log1p(1/(len(filename) + 2)) # Используем 1, т.к. слово точно не в spam_words

p_legit = m.log1p(len(legitname)/all_letters_num)

# ... остальной код
