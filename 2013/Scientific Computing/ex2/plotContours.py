# -*- coding: utf-8 -*-
"""
Created on Tue Mar 18 18:19:33 2014

@author: tmm13
"""

import matplotlib
import numpy as np
import matplotlib.cm as cm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

#t = np.loadtxt("SOR2D.txt", delimiter = "\t")

t = []
inFile = open("MQtest.txt", "r")
data = inFile.read()
data = data.split("\n")
for line in data[:-1]:
    line = line.split(",")
    for i in range(0,len(line)-1):
        try:
            line[i] = float(line[i])
        except ValueError:
            print "error with character ", line[i]
    t.append(line[:-1])
    
t = np.array(t)

x = np.linspace(0, 1, len(t[0]))
y = np.linspace(0, 1, len(t[0]))

plt.figure()

levels = np.arange(0,1,0.025)
norm = cm.colors.Normalize(vmax = abs(t).max(), vmin = abs(t).min())
cmap = cm.spectral

cset1 = plt.contour(x, y, t, levels,
                        cmap=cm.get_cmap(cmap, len(levels)-1),
                        norm=norm,
                        )

#plt.contour(x,y,t)    

inFile.close()