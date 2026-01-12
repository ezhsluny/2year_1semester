import numpy as np

p = 0.3
with open("python/l4/file1.txt") as f:
    line = f.readline()
    num_list1 = list(map(int, line.split()))
with open("python/l4/file2.txt") as f:
    line = f.readline()
    num_list2 = list(map(int, line.split()))


if len(num_list1) != len(num_list2):
    print("lists have different length")
else:
    #1st way: random choice by index and replacement after
    n = round(p * len(num_list2))
    res1 = np.array(num_list1)
    synth_data_idx = np.random.choice((len(num_list1)), n, replace=False)
    num_list2 = np.array(num_list2)
    res1[synth_data_idx] = num_list2[synth_data_idx]
    print(res1)


    #2nd way: with bool mask, shuffled and then implied to initial data
    mask = [True]*round(len(num_list1)*p) + [False]*(len(num_list1) - round(len(num_list1)*p))
    np.random.shuffle(mask)
    res2 = np.where(mask, num_list2, num_list1)
    print(res2)
