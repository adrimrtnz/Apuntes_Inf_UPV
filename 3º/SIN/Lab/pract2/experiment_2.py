import sys
import math
import numpy as np

from perceptron import perceptron
from confus import confus
from linmach import linmach

# python experiment.py OCR_14x14 "0.1 1 10 100 1000 10000" "0.1 1 10 100 1000 10000"
if len(sys.argv) != 4:
    print(f'Usage: {sys.argv[0]} <data> <alphas> <bs>')
    sys.exit(1)

data = np.loadtxt(sys.argv[1])
alphas = np.fromstring(sys.argv[2], sep=' ')
bs = np.fromstring(sys.argv[3], sep=' ')

N,L = data.shape
D=L-1 
labels=np.unique(data[:,D])  
C=labels.size 

np.random.seed(23)
perm=np.random.permutation(N)
data = data[perm]

NTr = int(round(.8*N))
M = N-NTr
train = data[:NTr,:]
test = data[NTr:,:]

# variables para el resumen de mejores resultados
best_alpha = best_beta = best_r = .0
best_iter = 0
min_perr = float('inf')

print('#      a       b    E   k  Ete Ete (%)      Ite (%)')
print('#------- ------- ---- --- ---- ------- ------------')

for a in alphas:
    for b in bs:
        w,E,k = perceptron(train,b,a, 1000)
        rl = np.zeros((M,1))
        for n in range(M):
            rl[n] = labels[linmach(w,np.concatenate(([1], test[n,:D])))]
        nerr,m = confus(test[:,D].reshape(M,1), rl)
        perr = nerr/M
        r = 1.96*math.sqrt(perr*(1-perr)/M)
        print(f' {a:7.1f} {b:7.1f} {E:4d} {k:4d} {int(nerr):3d} {perr*100:7.1f} [{(perr-r)*100:3.1f}, {(perr+r)*100:3.1f}]')

        # Guarda info de mejor caso
        if perr < min_perr:
            best_alpha = a
            best_beta = b
            best_r = r
            min_perr = perr
            best_iter = k

print('\n--------------TABLA DE MEJOR RESULTADO---------------------')
print('           Task       a       b Ete (%)      Ite (%)      k')
print('--------------- ------- ------- ------- ------------ ------')
print(f'{sys.argv[1]:>15s} {best_alpha:7.1f} {best_beta:7.1f} {min_perr*100:7.1f} [{(min_perr-best_r)*100:3.1f}, {(min_perr+best_r)*100:3.1f}] {best_iter:>6d}')