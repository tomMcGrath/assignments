# -*- coding: utf-8 -*-
"""
Created on Mon Feb 10 16:35:06 2014

@author: tmm13
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats.mstats import moment

def R1(t1,t2):
    # autocorrelation function
    gamma = np.float32(1)
    omega_0_sq = np.float32(2)
    delta = np.sqrt(omega_0_sq - gamma**2)
    rVal = np.exp(np.float32(-gamma*abs(t1-t2)))*(np.cos(np.float32(delta*abs(t1-t2))) - (1/delta)*np.sin(np.float32(delta*abs(t1-t2))))    
    return rVal
    
def R2(t1,t2):
    if np.abs(t1-t2) < 1:
        rVal = (2+np.abs(t1-t2))*(1-np.abs(t1-t2))*(1-np.abs(t1-t2))
    else:
        rVal = 0
    return rVal
    
def RMQ(t1, t2):
    a = 1
    rVal = np.exp(-a*np.abs(t1-t2))
    return rVal
    
def loop(function, timeLength, timeStep):
    t = np.arange(0, timeLength+timeStep, timeStep)
    x = np.zeros(len(t))
    gamma = np.zeros((len(t),len(t)))
    for i in range(0, len(t)):
        for j in range(0, len(t)):
            gamma[i][j] = function(t[i],t[j])
    eigval, eigvect = np.linalg.eig(gamma)
    #lambdaMatrix = eigvect*np.sqrt(eigval)*eigvect
    lambdaMatrix = np.dot(eigvect,np.sqrt(np.diagflat(eigval))).dot(eigvect.T)
    x = np.dot(lambdaMatrix,np.random.randn(len(t)))
    return x, gamma, eigval, eigvect, lambdaMatrix
    
def q2a(function, runs):
    samplesHolder = []
    posnHolder = []
    rmsSeries = []
    for i in range(0, runs):
        x, gamma, eigval, eigvect, lambdaMatrix = loop(function,10,0.1)
        samplesHolder.append(x)
        plt.plot(x,color='grey', alpha=0.5)
    plt.plot(np.mean(samplesHolder, axis=0),linewidth=2, color = 'black')
    plt.plot(moment(samplesHolder, moment = 2, axis=0), linewidth=2, color = 'blue')
    plt.plot(moment(samplesHolder, moment = 3, axis=0), linewidth=2, color = 'green')
    plt.plot(moment(samplesHolder, moment = 4, axis=0), linewidth=2, color = 'red')
    
    for sample in samplesHolder:
        posList = []
        for i in range(0,len(sample)):
            posList.append(sum(sample[0:i]))
        posnHolder.append(posList)
        
    return posnHolder
    
def calcRMS(posnHolder):
    mean = np.mean(posnHolder, axis = 0)
    RMS = mean**2
    return RMS

def q2b():
    # sample size 100000 gives xGT2 = 48743, 48914
    xGT2 = 0
    for i in range(0,100000):
        x, gamma, eigval, eigvect, lambdaMatrix = loop(R2,2,0.1)
        if max(x) > 2:
            xGT2 += 1
    print xGT2
    
    