import numpy as np

data = np.loadtxt('OCR_14x14')
w = np.loadtxt('percep_w')
N,L = data.shape
D = L-1
labels = np.unique(data[:,D])
C = labels.size

for n in range(N):
    for c in range(C):
        xn = np.concatenate(([1], data[n,:D]))
        print('g_%d(x_%d)=%.0f ' % (c, n, np.dot(w[:,c],xn)), end='')
    print('')