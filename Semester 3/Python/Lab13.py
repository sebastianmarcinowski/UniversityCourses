import numpy as np

# Zadanie 1
def zad1():
    n = int(input("Podaj rozmiar macierzy: "))
    A = np.ones((n,n),dtype=int)
    for r in range(0,A.shape[0]):
        for i in range(A.shape[0]):
            A[i,r] = (i+1)**r
    print(A)
zad1()
# Zadanie 2
def zad2():
    n = int(input("Podaj rozmiar macierzy: "))
    A = np.ones((n,n),dtype=int)
    for i in range(A.shape[0]):
        l = list(range(i*n+1,(i+1)*n+1))
        if(i%2==0):
            A[i:] = l
        else:
            A[i:] = l[::-1]
    print(A)

# Zadanie 4
def zad4():
    n = int(input("Podaj rozmiar macierzy: "))
    A = np.ones((n,n),dtype=int)
    for i in range(A.shape[0]):
        l = list(range(i*n+1,(i+1)*n+1))
        if(i%2==0):
            A[i:] = l
        else:
            A[i:] = l[::-1]
    A[(A%3==0) | (A%5==0)] = 0
    print(A)

# Zadanie 5
def zad5():
    ls = {1:[2,4,6], 2:[3], 3:[], 4:[], 5:[4,5], 6:[3]}
    S = np.zeros((len(ls.keys()),len(ls.keys())), dtype=int)
    for row in range(0,S.shape[0]):
        for elem in range(0,S.shape[0]):
            if(((row+1) in ls.keys()) & ((elem+1) in ls.get((row+1)))):
                S[row,elem] = 1
    # print(S)
    I = np.zeros((len(ls.keys()),sum([len(ls[x])for x in ls])),dtype=int)
    for row in range(0,S.shape[0]):
        for elem in range(0,S.shape[0]):
            if(((row+1) in ls.keys()) & ((elem+1) in ls.get((row+1)))):
                S[row,elem] = 1
    print(I)

# Zadanie 6
