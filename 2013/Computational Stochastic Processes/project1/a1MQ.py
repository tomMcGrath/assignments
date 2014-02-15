# -*- coding: utf-8 -*-
"""
Created on Fri Feb 14 13:18:24 2014

@author: tmm13
"""

import numpy as np

def kernel(x,y):
    a = 1
    rVal = np.exp(-a*np.abs(x-y))
    return rVal

