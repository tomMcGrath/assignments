# -*- coding: utf-8 -*-
"""
Created on Thu May  1 14:51:06 2014

@author: tmm13
"""


import matplotlib
import numpy as np
import matplotlib.cm as cm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

t=[0]
inFile = open("q4.txt", "r")
data = inFile.read()
data = data.split("\n")
for line in data[:-1]:
    t.append(float(line))

t.append(0)

t = np.array(t)
x = np.linspace(0,1,len(t))

fig = plt.figure()
ax = fig.add_subplot(111)

graph1 = ax.plot(x,t)
ax.set_xlabel("x")
ax.set_ylabel("Psi")
ax.set_title("Solution of Poisson's equation on the unit line")