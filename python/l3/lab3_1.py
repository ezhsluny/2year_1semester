"""
1. Реализовать два класса Pupa и Lupa. И класс Accountant.
2. Класс Accountant должен уметь одинаково успешно работать и с экземплярами 
класса Pupa и с экземплярами класса Lupa. У класса Accountant должен быть метод give_salary(worker). 
Который, получая на вход экземпляр классов Pupa или Lupa, вызывает у них метод take_salary(int). 
Необходимо придумать как реализовать такое поведение. Метод take_salary инкрементирует внутренний 
счётчик у каждого экземпляра класса на переданное ему значение.
3. При этом Pupa и Lupa два датасайнтиста и должны работать с матрицами. У них есть
метод do_work(filename1, filename2). Pupa считывают из обоих переданных ему файлов по 
матрице и поэлементно их суммируют. Lupa считывают из обоих переданных ему файлов по матрице и 
поэлементно их вычитают. Работники обоих типов выводят результат своих трудов на экран.
"""


def line_to_list(row):
    """
    Returns the string converted to int list
    """


    if row[-1] == '\n':
        tmp = list(row[:-1].split(' '))
    else:
        tmp = list(row.split(' '))
    for i in range(len(tmp)):
        tmp[i] = int(tmp[i])

    return tmp



def print_matrix(m):
    """
    Prints matrix without commas and parenthesis
    """
    for i in range(len(m)):
        for j in range(len(m[0])):
            print(str(m[i][j]), end=' ')
        print()


def read_matrices(filename1, filename2):
    m1 = []
    m2 = []
    with open(filename1) as f:
        while True:
            a = f.readline()
            if a == '':
                break
            else:
                m1.append(line_to_list(a))
    with open(filename2) as f:
        while True:
            a = f.readline()
            if a == '':
                break
            else:
                m2.append(line_to_list(a))
    return m1, m2


class Pupa():
    def __init__(self, salary=0):
        self._salary = salary
    
    def take_salary(self, num):
        self._salary += num

    def do_work(self, filename1, filename2):
        m1, m2 = read_matrices(filename1, filename2)

        m = []
        for i in range(len(m1)):
            c = []
            for j in range(len(m1[0])):
                tmp = m1[i][j] + m2[i][j]
                c.append(tmp)
            m.append(c)        
        
        print_matrix(m)

    def __str__(self):
        """ Вызов как строки """
        return f"pupa worker's salary: {self._salary}" 


class Lupa():
    def __init__(self, salary=0):
        self._salary = salary
    
    def take_salary(self, num):
        self._salary += num

    def do_work(self, filename1, filename2):
        m1, m2 = read_matrices(filename1, filename2)

        m = []
        for i in range(len(m1)):
            c = []
            for j in range(len(m1[0])):
                tmp = m1[i][j] - m2[i][j]
                c.append(tmp)
            m.append(c)        
        
        print_matrix(m)

    def __str__(self):
        """ Вызов как строки """
        return f"lupa worker's salary: {self._salary}" 


class Accountant(Pupa, Lupa):
    def __init__(self, salary_size=70000):
        self._salary_size = salary_size

    def give_salary(self, worker):
        worker.take_salary(self._salary_size)


f1 = "python/input1.txt"
f2 = "python/input2.txt"
pupa = Pupa()
lupa = Lupa()
print(pupa, lupa, end='\n\n')
pupa.do_work(f1, f2)
print()
lupa.do_work(f1, f2)
print()
accountant = Accountant()
accountant.give_salary(pupa)
accountant.give_salary(lupa)
print(pupa, lupa)