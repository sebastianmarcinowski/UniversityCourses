import numpy as np
import scipy as sp
import random as r
import math
# Zadanie 1
# A = np.arange(1, 21, 1)
# A.resize(4,5)
# A = +A.T
# print(A)

# Zadanie 2
# A = np.array([[8,1,2,16],[5,-3,-7,-22],[0,-5,7,11]])
# n = np.size(A[:,0])
# b = A[:,n]
# A = A[:,0:n]
# w = np.linalg.det(A)
# def Cramer(A):
#     if(w == 0):
#         print("Wyznaczik jest rowny 0")
#     else:
#         for i in range(0,n):
#             temp = A.copy()
#             temp[:,i] = b
#             wt = np.linalg.det(temp)
#             zmienna = wt/w
#             print(zmienna)
# Cramer(A)

# Zadanie 3
A = np.array([[0,0,0,0,0,0],[0,1,0,0,1,0],[0,1,0,0,1,0],[0,1,0,0,1,0],[0,0,1,1,0,0],[0,0,0,0,0,0],])
A = np.flip(A,0.5)
print(A)

# Zadanie 4
# A = np.ones((2,2))
# B = np.zeros((2,1))
# D = np.hstack((B,A,B))
# D = np.vstack((D,(np.hstack((B.T,B.T)))))
# D = np.hstack((D,np.vstack((B.T,A))))
# print(D)

# Zadanie 5
# A = np.arange(0,21,2)
# B = np.arange(3,34,3)
# A = np.hstack((A,B))
# A = np.sort((A*(-1)), axis =0, kind='quicksort')
# print(A*(-1))

# Zadanie 6
# def xd(n,m):
#     A = np.random.randint(2,22,(n,m))
#     for i in range(0,n):
#         for j in range(0,m):
#             if(A[i,j]%2==0):
#                 A[i,j] = -100
#             else:
#                 A[i,j] = 100
#     print(A)
# xd(4,4)

# Zadanie 7
# A = np.random.rand(1,20)
# for i in range(np.size(A)):
#     if(A[0,i] < 0.33):
#         A[0,i] = r.randint(10,100)
#     elif(0.67 >= A[0,i] >=0.33):
#         A[0,i] = r.random()
#     else:
#         A[0,i] = A[0,i]*5+5
#     round(A[0,i],3)
# print(A.T)

