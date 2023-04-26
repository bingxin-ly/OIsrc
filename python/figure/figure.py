from ctypes import *
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

lib = cdll.LoadLibrary('python/lib.so')
lib.call0.argtypes = [c_double]
lib.call0.restype = c_double
lib.call1.argtypes = [c_double]
lib.call1.restype = c_double

m = 500
n = 10 * m
x = np.linspace(0.5, m, n)
y0 = np.ndarray(shape=(n, 1), dtype=float)
y1 = np.ndarray(shape=(n, 1), dtype=float)
for i in range(n):
    y0[i] = lib.call0(x[i])
    y1[i] = lib.call1(x[i])
y2 = np.divide(1, x)

fig, ax = plt.subplots()
ax.plot(x, y0)
ax.plot(x, y1)
# ax.plot(x, y2)
plt.show()
