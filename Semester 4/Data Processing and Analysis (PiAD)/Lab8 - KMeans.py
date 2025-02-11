import numpy as np
import scipy as sp
import scipy.sparse
import matplotlib.pyplot as plt
import pandas as pd
from sklearn import metrics
from sklearn import datasets
from sklearn.decomposition import PCA
from statistics import mode
from sklearn.neighbors import KDTree, KNeighborsClassifier
import time
from collections import Counter

def distp(X,C):
    dist = np.sqrt(np.sum((X-C)**2))
    return dist

def distm(X,C):
    s = X - C
    V = np.array(np.cov(X))
    print(V)
    V = np.linalg.inv(V)
    # dist = np.sqrt((X-C)*(V**-1)*((X-C).T))
    dist = np.sqrt(np.dot(np.dot(X.T, V), X))
    # print(dist)
    return dist

def ksrodki(X,k,max_iter=10):
    # Losowe wybranie punktow startowych
    C = {}
    for i in range(k):
        id = np.random.randint(0,len(X))
        center = X[id]
        points = []
        node ={"center":center,
                "points":points}
        C[i] = node
    for _ in range(max_iter):
        # Przypisanie punktów do najbliszego środka
        for i in range(X.shape[0]):
            dist = []
            x = X[i]
            for j in range(k):
                dist.append(distp(x,C[j]["center"]))
            curr_c = np.argmin(dist)
            # print(curr_c)
            C[curr_c]["points"].append(x)
        # Oblicznie jakosci zgrupowania
        B = [C[i]["center"] for i in range(k)]
        #print(type(B))
        B = [[arr.tolist() for arr in B[i]] for i in range(k)]
        B = np.array(B)
        Ck = []
        for i in range(k):
            Ck.append(B[i,:])
        fcmian = 0
        fclicz = 0
        for i in range(k-1):
            for x in Ck:
                fclicz += distp(Ck[i],Ck[i+1])
        for i in range(k):
            for x in Ck:
                fcmian += distp(x,Ck[i])**2
        FC = fclicz/fcmian
        print("F(C) = ", FC)
        # Zmiana pozycji środków
        new_C = {}
        for i in range(k):
            points = np.array(C[i]["points"])
            new_center = C[i]["center"]
            new_points = C[i]["points"]
            if(points.shape[0]>0):
                new_center = [points[:,0].mean(),points[:,1].mean()]
                new_points = []
            new_node={"center":new_center,
                         "points":new_points}
            new_C[i] = new_node
        # Sprawdzenie czy środki się zmieniły, jeżeli tak przerwanie pętli
        compC = np.array([C[i]["center"] for i in range(k)])
        compnew_C = np.array([new_C[i]["center"] for i in range(k)])
        #print(compC)
        #print(compnew_C)
        if (compC in compnew_C):
            break
        C = new_C
    CX = [C[i]['points'] for i in range(k)]
    C = [C[i]['center'] for i in range(k)]
    C = [[arr.tolist() for arr in C[i]] for i in range(k)]
    CX = [[arr.tolist() for arr in CX[i]] for i in range(k)]
    C = np.array(C)
    return C, CX

plik = pd.read_csv("Lab8/autos.csv")
X,y = datasets.make_blobs(n_samples = 500,n_features = 2,centers = 3,random_state = 23)
# print(X)
X = plik[['wheel-base', 'length']]
X = np.array(X)
# print(X)
# y = plik.target
C, CX = ksrodki(X,k=4)

# Zadanie 3
C = np.array(C)
for i in range(len(CX)):
    points = np.array(CX[i])
    #print(np.ndim(points))
    if(points.shape[0]>0):
        plt.scatter(points[:,0],points[:,1])
plt.scatter(C[:,0],C[:,1],c='black')
plt.show()