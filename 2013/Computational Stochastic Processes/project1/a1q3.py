# -*- coding: utf-8 -*-
"""
Created on Wed Feb 12 10:48:55 2014

@author: tmm13
"""

import numpy as np
from scipy.integrate import quad
import matplotlib.pyplot as plt

def plotCM(covMat):
    series1 = []
    series2 = []
    series3 = []
    series4 = []
    for i in covMat:
        series1.append(i[0][0])
        series2.append(i[1][0])
        series3.append(i[0][1])
        series4.append(i[1][1])
    plt.plot(series1)
    plt.plot(series2)
    plt.plot(series3)
    plt.plot(series4)

def answerQ3(numRuns, timeLength, timeStep):
    resultsHolder = []
    covMatHolder = []
    t = np.arange(0,timeLength,timeStep)
    #t = np.arange(0,timeLength+timeStep, timeStep)
    for i in range(0,numRuns):
        resultsHolder.append(simulate(timeLength,timeStep))
    for j in range(0,len(t)):
        temp = np.zeros((2,len(resultsHolder)))
        for i in range(0, len(resultsHolder)):
            temp[0][i] = resultsHolder[i][j][0]
            temp[1][i] = resultsHolder[i][j][1]
        covMatHolder.append(np.cov(temp))
    mean = np.mean(resultsHolder, axis = 0)
    return resultsHolder, mean, covMatHolder    

def plotPath(path):
    xSeries = []
    ySeries = []
    for i in path:
        xSeries.append(i[0])
        ySeries.append(i[1])
    plt.plot(xSeries)
    plt.plot(ySeries)
    
def plotMeanAndVar(samples):
    fig = plt.figure()
    ax1 = fig.gca()
    errorSeries = []
    varSeries = []
    for N in range(1, len(samples)):
        error = np.mean(samples[0:N])
        errorSeries.append(error)
        varSeries.append(np.var(samples[0:N]))
    ax1.plot(errorSeries)
    ax2 = ax1.twinx()
    ax2.plot(varSeries, color = 'g')
    ax1.set_xlabel('Number of samples')
    ax1.set_ylabel('Mean')
    ax2.set_ylabel('Variance')

def simulate(timeLength,timeStep):
    path = []
    t = np.arange(0,timeLength+timeStep,timeStep)
    path.append(np.array([0,0]))
    for i in range(1,len(t)-1):
        path.append(path[i-1] + generateIncrement(t[i],t[i+1]))
    return path
    
def generateIncrement(t1,t2):
    gamma = calcGamma(t1,t2)
    mu = calcMu(t1,t2)
    increment = np.random.multivariate_normal(mu,gamma)
    return increment

def calcGamma(t1,t2):
    gammaMatrix = np.zeros([2,2])
    gammaMatrix[0,0] = quad(gamma11,t1,t2)[0]
    gammaMatrix[1,0] = quad(gamma12,t1,t2)[0]
    gammaMatrix[0,1] = quad(gamma21,t1,t2)[0]
    gammaMatrix[1,1] = quad(gamma22,t1,t2)[0]
    return gammaMatrix
    
def gamma11(t):
    rVal = 1.25 + 0.1*np.cos(t)*np.cos(t) + 0.01*np.cos(t)*np.cos(t)*np.cos(t)*np.cos(t)
    return rVal
    
def gamma12(t):
    rVal = 1.3 + 0.2*np.cos(t)*np.cos(t)
    return rVal
    
def gamma21(t):
    return gamma12(t) # gamma12=gamma21 because covariance is symmetric
    
def gamma22(t):
    rVal = 4.09
    return rVal

def calcMu(t1,t2):
    muMatrix = np.zeros([2])
    muMatrix[0] = quad(mu1,t1,t2)[0]
    muMatrix[1] = quad(mu2,t1,t2)[0]
    return muMatrix
    
def mu1(t):
    rVal = 2*t
    return rVal
    
def mu2(t):
    rVal = 0.1*t
    return rVal