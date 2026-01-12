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


def read_matrices_from_file(filepath):
    """
    Reads matrices from the file

    Parameters
    ----------
    filepath : str
        The string which contains path to the file
    
    Returns
    -------
    m1 : int list of lists
        The first matrix from the file converted to int values
    m2 : int list of lists
        The second matrix from the file converted to int values
    """


    with open(filepath) as f:
        m1 = []
        while True:
            a = f.readline()
            if a == '\n':
                break
            else:
                m1.append(line_to_list(a))
        m2 = []
        while True:
            a = f.readline()
            if a == '':
                break
            else:
                m2.append(line_to_list(a))

    return m1, m2


def matrix_convolution(m1, m2):
    m1_x = len(m1[0])
    m1_y = len(m1)
    m2_x = len(m2[0])
    m2_y = len(m2)
    m3_x = m1_x - m2_x + 1
    m3_y = m1_y - m2_y + 1

    m3 = []
    for i in range(m3_y):
        c = []
        for j in range(m3_x):
            tmp = 0
            for u in range(m2_x):
                for v in range(m2_y):
                    a = m1[i + u][j + v]
                    b = m2[u][v]
                    tmp += a * b
            c.append(tmp)
        m3.append(c)
    return m3


def write_matrix(m, filepath):
    """
    Prints matrix without commas and parenthesis into output file
    """
    with open(filepath, "w") as f:
        for i in range(len(m)):
            for j in range(len(m[0])):
                f.write(str(m[i][j]) + ' ')
            f.write('\n')


# import argparse


# parser = argparse.ArgumentParser(prog='pascal_triangle')
# parser.add_argument('input_file')
# parser.add_argument('output_file')
# args = parser.parse_args()
# f_in = args.input_file
# f_out = args.output_file

f_in = '/home/ezhsluny/Documents/python/input.txt'
f_out = '/home/ezhsluny/Documents/python/output.txt'

a, b = read_matrices_from_file(f_in)
c = matrix_convolution(a, b)
write_matrix(c, f_out)