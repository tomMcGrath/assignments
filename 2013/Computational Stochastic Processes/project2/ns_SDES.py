# -*- coding: utf-8 -*-
"""
Created on Mon Mar 03 12:35:13 2014

@author: tmm13
"""

import numpy as np

def EM(func, end, stepsize):
    t = np.arange(0,end,stepsize)
    x = np.arange(0,end,stepsize)
    y = np.arange(0,end,stepsize)
    k = 0.1
    rvs = 2.0*k*np.random.randn(2, len(t)) # vectorise