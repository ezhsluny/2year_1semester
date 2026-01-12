import matplotlib.pyplot as plt
import math as m
import numpy as np
import random


t = np.arange(100, 10000, 10)

p = []
for i in t:
    n = 0
    for j in range(i):
        x = random.uniform(0, 1)
        y = random.uniform(0, 1)
        if (m.sqrt((x - 0.5) ** 2 + (y - 0.5) ** 2) < 0.5):
            n += 1
    pokr = n / i
    p.append(pokr * 4)


plt.axis([0, 10000, 2.9, 3.9])
plt.plot(t,p)
plt.axhline(y=3.14159, color='r', linestyle='--')
plt.show()