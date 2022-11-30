import numpy as np

def perceptron(data, b=0.1, a=1.0, K=200):
  (N, L) = data.shape; D = L-1
  labels = np.unique(data[:, D])
  C = labels.size
  w = np.zeros((L, C))
  for k in range(1, K+1):
    E = 0
    for n in range(N):
      xn = np.concatenate(([1], data[n, :D]))
      cn = np.where(labels==data[n, D])[0][0]
      err = False; g = np.dot(w[:, cn], xn)
      for c in range(C):
        if c != cn and np.dot(w[:,c],xn)+b > g:
          w[:, c] = w[:, c] - a*xn; err = True
      if err == True:
        w[:, cn] = w[:, cn] + a*xn; E = E+1
    if E == 0: 
      break
  return w,E,k
