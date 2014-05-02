# -*- coding: utf-8 -*-
"""
Created on Thu May  1 11:22:44 2014

@author: tmm13
"""
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def countSN(N):
    if N == 2:
        return(0)
        
    else:
        count = 0
        count += countSN(N/2)
        count += countTN(N/2)
        count += (N-1)
        return(count)
        
def countTN(N):
    if N == 2:
        return(3)
    else:
        count = 0
        count += countTN(N/2)
        count += countUN(N/2)
        count += N
        return(count)

def countUN(N):
    if N == 2:
        return(6)
    else:
        count = 0
        count += countTN(N/2)
        count += countTN(N/2)
        count += (7*N)-2
        return(count)        
        
"""
Operations counting code
"""        
        
        
Nvals = []
results = []
NlogN = []
N2 = []
N = 2

while (N <= 2097152):
    Nvals.append(N)
    results.append(countSN(N))
    NlogN.append(N*np.log2(N))
    N2.append(N*N)
    N *= 2



"""
Curve fitting code
"""

def func(N,a2,b2):
    return a2*N*np.log2(N) + b2*N

x = np.array(Nvals)
y = np.array(results)

params, cov = curve_fit(func, x, y)

synData = []
for N in Nvals:
    synData.append(func(N, params[0], params[1]))
    
    
fig = plt.figure()
ax = fig.add_subplot(111)
graph1 = ax.plot(Nvals, results, label = "W_SN")
graph2 = ax.plot(Nvals, NlogN, label = "N log2 N")
graph3 = ax.plot(Nvals, N2, label = "N^2")
graph4 = ax.plot(Nvals, synData, label = "fitted curve", color="black")
ax.set_yscale('log', basey=2)
ax.set_xscale('log', basex=2)
ax.set_xlabel('N')
ax.set_ylabel('Number of operations')

handles, labels = ax.get_legend_handles_labels()

# reverse the order
ax.legend(handles[::-1], labels[::-1], loc = 2)








