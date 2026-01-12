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


def multiply_matrices(m1, m2):
    """
    Returns a matrix - result of multiplying matrix m1 and matrix m2
    """


    m = []
    l_row = len(m2)
    l_col = len(m1[0])
    if l_row != l_col:
        print("Matrices can't be multiplied")
    else:
        for i in range(len(m1)):
            c = []
            for j in range(len(m2[0])):
                tmp = 0
                for k in range(len(m2)):
                    x = m1[i][k]
                    y = m2[k][j]
                    tmp += m1[i][k] * m2[k][j]
                c.append(tmp)
            m.append(c)        
    
    return m


def write_matrix(m, filepath):
    """
    Prints matrix without commas and parenthesis into output file
    """
    with open(filepath, "w") as f:
        for i in range(len(m)):
            for j in range(len(m[0])):
                f.write(str(m[i][j]) + ' ')
            f.write('\n')


import argparse


parser = argparse.ArgumentParser(prog='pascal_triangle')
parser.add_argument('input_file')
parser.add_argument('output_file')
args = parser.parse_args()
f_in = args.input_file
f_out = args.output_file


a, b = read_matrices_from_file(f_in)
c = multiply_matrices(a, b)
write_matrix(c, f_out)