import numpy as np

# #1
# arr = np.random.randint(-3, 3, size=10)
# unique_el, freq_el = np.unique(arr, return_counts=True)
# print(arr)
# print(unique_el[np.argsort(freq_el)])
# print("--------------------------\n")


# #2
# h = 10
# w = 4
# image = np.random.randint(0, 256, size=(w, h), dtype=np.uint8)
# print("Уникальные цвета", np.unique(image), len(np.unique(image)))
# print("--------------------------\n")


#3
vec = np.arange(-2, 2, 0.6, dtype=float)
print(vec)
print("set range of the average value: \n")
a = int(input("a: "))
b = int(input("b: "))
if (a < 0 or a > len(vec) or b < 0 or b > len(vec) or a > b):
    print("invalid range")
else:
    new_vec = []
    while True:
        if b + 1 <= len(vec):
            piece = vec[a:b + 1]
            sum = np.average(piece)
            new_vec.append(sum)
            a += 1
            b += 1
        else:
            break
    new_vec = np.array(new_vec)
    print(new_vec)
print("Floating average vec: ", np.average(new_vec))
print("--------------------------\n")


# #4
# n = 5
# num_triads = np.random.randint(0, 100, size=(n, 3), dtype=np.uint8)
# a_bool = num_triads[:, 0] + num_triads[:, 1] > num_triads[:, 2]
# b_bool = num_triads[:, 0] + num_triads[:, 2] > num_triads[:, 1]
# c_bool = num_triads[:, 2] + num_triads[:, 1] > num_triads[:, 0]
# print(num_triads)
# res = a_bool & b_bool & c_bool
# good_idxs = np.where(res == True)
# triangles = []
# for i in good_idxs:
#     triangles.append(num_triads[i])
# print(triangles)
# print("--------------------------\n")


# #5
# coefs = np.array([[3,4,2], [5,2,3],[4,3,2]],)
# coefs_x = np.array([[17,4,2], [23,2,3],[19,3,2]])
# coefs_y = np.array([[3,17,2], [5,23,3],[4,19,2]])
# coefs_z = np.array([[3,4,17], [5,2,23],[4,3,19]])
# det = np.linalg.det(coefs)
# det_x = np.linalg.det(coefs_x)
# det_y = np.linalg.det(coefs_y)
# det_z = np.linalg.det(coefs_z)
# print("x = ", np.round(det_x/det_y), "\ny = ", np.round(det_y/det), "\nz = ", np.round(det_z/det))
# print("--------------------------\n")


# #6
# A = np.matrix("1 0 1; 0 1 0; 1 0 1")

# U, S, V = np.linalg.svd(A)
# print(np.round((U @ np.diag(S)) @ V))
