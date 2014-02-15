# -*- coding: utf-8 -*-
"""
Created on Wed Feb 05 14:21:41 2014
Computational Stochastic Processes Assignment 1 Question 1
@author: Tom McGrath
"""
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from matplotlib import cm
from scipy.integrate import dblquad
from scipy.stats import norm
import cPickle as pickle

# exp(-10*((x-0.5)^2 - (1/2)*(y+0.1)^4)) + exp(-10*((3/4)*(x+0.4)^2 - (y-0.5)^4)) - Wolfram Alpha snippet for comparison

def f(x,y):
    beta = 10
    xd = np.float32(x) # cast values as double-precision floats (so we only lose accuracy around 16th decimal)
    yd = np.float32(y)
    v1 = (xd - 0.5)*(xd - 0.5) - 0.5*(yd+0.1)*(yd+0.1)*(yd+0.1)*(yd+0.1) # the python np.power() command loses precision
    v2 = 0.75*(xd+0.4)*(xd+0.4) - (yd-0.5)*(yd-0.5)*(yd-0.5)*(yd-0.5)
    rVal = np.exp(-beta*v1) + np.exp(-beta*v2)
    return rVal
       
def psi():
    beta = 0.1
    mean = [-0.5, -1]
    cov = [[0.1, 0],[0, 0.1]]
    rVal = np.random.multivariate_normal(mean, cov)
    if (np.abs(rVal[0]) > 1 or np.abs(rVal[1]) > 1):
        rVal = [None,None]
    return rVal
    
def pdfPsi(x,y):
    xDist = norm(-0.5,0.1)
    yDist = norm(-1,0.1)
    rVal = xDist.pdf(x)*yDist.pdf(y)
    return rVal
    
def psi2():
    beta = 0.1
    mean1 = [-0.5,-1]
    cov1 = [[1, 0],[0, 1]]
    mean2 = [1, 0.5]
    cov2 = [[1,0],[0,1]]
    rVal = 0.5*np.random.multivariate_normal(mean1, cov1) + 0.5*np.random.multivariate_normal(mean2, cov2)
    if (np.abs(rVal[0]) > 1 or np.abs(rVal[1]) > 1):
        rVal = [None,None]
    return rVal
    
def pdfPsi2(x,y):
    xDist1 = norm(-0.5,1)
    yDist1 = norm(-1,1)    
    xDist2 = norm(1,1)
    yDist2 = norm(0.5,1)   
    rVal = 0.5*(xDist1.pdf(x)*yDist1.pdf(y)) + 0.5*(xDist2.pdf(x)*yDist2.pdf(y))
    return rVal
    
def MCLoop(function, numIters):
    samples = np.zeros(numIters)
    for i in range(0, numIters):
        [x_i, y_i] = np.random.uniform(-1, 1, 2) # we could also use antithetic variable sampling here
        samples[i] = 4*f(x_i, y_i)
        if i % 100000 == 0:
            print i
    return samples
    
def ISLoop(function, sampler, samplerPdf, numIters):
    samples = np.zeros(numIters)
    for i in range(0, numIters):
        [x_i, y_i] = sampler()
        if [x_i, y_i] == [None,None]:
            samples[i] = 0
        else:
            samples[i] = f(x_i, y_i)/(samplerPdf(x_i, y_i))
        #if samples[i] > 1e+22:
            #print x_i, y_i, f(x_i,y_i), samplerPdf(x_i, y_i)
        if i % 10000 == 0:
            print i
    return samples
    
def plotErrAndVar(samples):
    deterministicVal = integrate()
    fig = plt.figure()
    ax1 = fig.gca()
    errorSeries = []
    varSeries = []
    for N in range(1, len(samples)):
        error = np.mean(samples[0:N]) - deterministicVal[0]
        errorSeries.append(error)
        varSeries.append(calcVar(samples[0:N]))
    ax1.plot(errorSeries)
    ax2 = ax1.twinx()
    ax2.plot(varSeries, color = 'g')
    ax1.set_xlabel('Number of samples')
    ax1.set_ylabel('Error')
    ax2.set_ylabel('Variance')
    #ax.set_yscale('log')

def calcVar(samples):
    N = len(samples)
    sMean = np.mean(samples)
    varList = samples - sMean
    rVal = sum(varList**2)/N
    return rVal

def integrate():
    r = dblquad(f,-1,1,lambda x:-1,lambda x:1)
    return r
    
def plotSurface():
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    X = np.arange(-1, 1, 0.1)
    Y = np.arange(-1, 1, 0.1)
    X, Y = np.meshgrid(X, Y)
    Z = f(X,Y)
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.coolwarm,
        linewidth=0, antialiased=False)  
    ax.zaxis.set_major_locator(LinearLocator(10))
    #ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f')) 
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    fig.colorbar(surf, shrink=0.5, aspect=5)   
    ax.set_zscale('log')
    plt.show()
    maxSeries = []
    for i in range(0,len(Z)):
        maxSeries.append(max(Z[i]))
    print max(maxSeries)
    #return Z

def writeResults(function, length, checkpoint):
    # write data to disk, using a checkpoint system for long runs
    numRuns = int(length/checkpoint)
    print numRuns
    for i in range(0, numRuns):
        samples = MCLoop(function, checkpoint)
        pickle.dump(samples, open(str(i)+'.p', 'wb'))
        
        




