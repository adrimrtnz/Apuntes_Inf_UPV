#!/usr/bin/python
import numpy as np
from perceptron import perceptron

data=np.loadtxt('OCR_14x14');
N,L=data.shape;
np.random.seed(23); perm=np.random.permutation(N); data=data[perm];

w,E,k=perceptron(data,1000,0.1);
np.savetxt('OCR_14x14__w',w,fmt='%.2f');

print(w);