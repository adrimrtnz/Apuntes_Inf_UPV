import numpy as np

# N = número de filas (muestras en el data set)
# L = número de columnas (última columna es la clase)
# D = número de características
# C = número de clases

def perceptron(data,b=0.1,a=1.0,K=200):
    (N,L)=data.shape
    D=L-1
    labels=np.unique(data[:,D])
    C=labels.size
    w = np.zeros((L,C))    # vector de pesos inicialmente a 0
    for k in range(1,K+1):
        E=0;
        for n in range(N):
            xn=np.concatenate(([1],data[n,:D]))
            cn=np.where(labels==data[n,D])[0][0]
            err= False; g=np.dot(w[:,cn],xn)
            for c in range(C):
                # para toda clase distinta de la 'correcta'
                if c != cn and np.dot(w[:,c],xn) + b > g:
                    # Si clasifica mal 'castiga' clase mal elegida
                    w[:,c] = w[:,c] - a*xn;
                    err=True
                # si hay error, refuerza la clase a la que pertenece la muestra
            if err==True:
                w[:,cn] = w[:,cn] + a*xn; E=E+1
        if E==0: 
            break
    return w,E,k
