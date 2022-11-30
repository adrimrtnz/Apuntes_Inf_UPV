import numpy as np

def linmach(w,x):
    C = w.shape[1]
    cstar = None
    max_g = float('-inf')
    for c in range(C):
        g = np.dot(w[:,c], x)
        if g > max_g:
            max_g = g
            cstar = c
    return cstar
