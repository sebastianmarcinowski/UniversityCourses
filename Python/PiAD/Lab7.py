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
from sklearn.model_selection import LeaveOneOut, train_test_split
import time
from collections import Counter

def euc_distance(x1,x2):
    distance = np.sqrt(np.sum((x1-x2)**2))
    return distance

class KNN:
    def __init__(self, n_neighbours =1, use_KDTree = False):
        self.type = type
        self.n_neighbours = n_neighbours
        self.use_KDTree = use_KDTree
    
    def fit(self, X, y):
        self.X_train = X
        self.y_train = y
        if self.use_KDTree == True:
            self.KDTree = KDTree(X)
        return self.X_train,self.y_train
    
    def predict(self, X):
        prediction = []
        if self.use_KDTree == True:
            nv,id = self.KDTree.query(X,k=self.n_neighbours)
            for i in range(len(X)):
                pred = self.predict_help(id[i])
                prediction.append(pred)
        else:
            for i in range(len(X)):
                pred = self.predict_help(X[i],True)
                prediction.append(pred)
        self.predicion = prediction
        return prediction
        
    def predict_help(self,X, type = True):
        if self.use_KDTree == True:
            # X = np.array(X).reshape(-1,1)
            nv,id = self.KDTree.query(X,k=self.n_neighbours)
            kn_labels = [self.y_train[i] for i in id[0]]
        else:
            # Obliczanie odleglosci miedzy punktami
            distances = [euc_distance(X,X_train) for X_train in self.X_train]
            # Wybranie k najblizszych sasiadow
            k_id = np.argsort(distances)[:self.n_neighbours]
            kn_labels = [self.y_train[i] for i in k_id]
            # Wybranie najczesciej wystepujacej etykiety
        if type == True:
            most_common = mode(kn_labels)
        elif type == False:
            most_common = np.mean(kn_labels)
        return most_common
    
    def predict_regression(self,X):
        prediction = []
        if self.use_KDTree == True:
            nv,id = self.KDTree.query(X, k=self.n_neighbours)
            for i in range(len(X)):
                pred = np.mean([self.y_train[j] for j in id[i]])
                prediction.append(pred)
        else:
            for i in range(len(X)):
                prediction.append(self.predict_help(X[i],False))
        self.predicion = prediction
        return prediction

    def score_clf(self, X, y):
        acc = round(np.sum(self.predicion == y) / len(y),4)
        #print(acc)
        return acc

    def score_reg(self,X,y):
        acc = metrics.mean_squared_error(y,self.predicion)
        #print("Błąd średniokwadratowy: ")
        #print(acc)
        return acc

#! Klasyfikacja
# Zadanie 1
X,y = datasets.make_classification(
    n_samples=100,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_repeated=0,
    random_state=3
)
plt.plot(X[:,0][y==0],X[:,1][y==0],'o')
plt.plot(X[:,0][y==1],X[:,1][y==1],'ro')
plt.show()
Xvs = 21
Xv1 = np.array([[np.random.uniform(np.min(X[:,0])*0.8,np.max(X[:,0])*0.8)]for x in range(Xvs)])
Xv2 = np.array([[np.random.uniform(np.min(X[:,1])*0.8,np.max(X[:,1])*0.8)]for x in range(Xvs)])
X_value = np.hstack((Xv1,Xv2))
y_value = np.random.randint(0,2,Xvs)

# Zadanie 2
clf = KNN(n_neighbours=2)
clf.fit(X,y)
pr = clf.predict(X)
clf.score_clf(X,y)
n = KNeighborsClassifier(n_neighbors=7)
n.fit(X,y)
n.predict(X)
print("Wartosc funkcji score dla wbudowanego KNN")
print(n.score(X,y))

# Zadanie 3
# Granica separacji
h = 0.1  # krok siatki
xx, yy = np.meshgrid(np.arange(X[:,0].min()-.2, X[:,0].max()+.2, h),
                        np.arange(X[:,1].min()-.2, X[:,1].max()+.2, h))
Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
# ravel - wyplaszcza tablice danych
# c_ - zlacza tabele wedle drugiego wymiaru
Z = np.array(Z).reshape(xx.shape)
plt.contourf(xx, yy, Z)
plt.plot(X[:,0][y==0],X[:,1][y==0],'o')
plt.plot(X[:,0][y==1],X[:,1][y==1],'ro')
plt.title("Granica separacji")
plt.show()

# Zadanie 4
iris = datasets.load_iris()
X = iris.data
y = iris.target
clfzad4 = KNN(n_neighbours=3)
clfzad4.fit(X,y)
pr2 = clfzad4.predict(X)
print("Wartosc klasyfikacji zadanie 4")
score = clfzad4.score_clf(X,y)
print(score)

# Zadanie 5
iris = datasets.load_iris()
X = iris.data
y = iris.target
pca = PCA(n_components=2)
X_r = pca.fit(X).transform(X)
xx, yy = np.meshgrid(np.linspace(X_r[:,0].min(), X_r[:,0].max(), 100),
                    np.linspace(X_r[:,1].min(), X_r[:,1].max(), 100))
Z = np.vstack([xx.ravel(), yy.ravel()]).T
clfzad5 = KNN(1)
clfzad5.fit(X,y)
data4D = pca.inverse_transform(Z)
pr = clfzad5.predict(data4D)
pr = np.array(pr).reshape(100,100)
plt.scatter(X_r[:,0],X_r[:,1],c=y)
plt.contour(xx,yy,pr)
plt.show()

# Zadanie 6
iris = datasets.load_iris()
X = iris.data
y = iris.target
wyniki = {'Wartosc k: ':[], 'score':[]}
kroswalidacja = LeaveOneOut() #inicjalizacja kroswalidacjj leave one out
for k in range(1,20):
    acc = []
    for train, test in kroswalidacja.split(X):
        X_train, X_test = X[train], X[test]
        y_train, y_test = y[train], y[test]
        clfzad6 = KNN(k)
        clfzad6.fit(X_train,y_train)
        pred = clfzad6.predict(X_test)
        acc.append(clfzad6.score_clf(X_test,y_test))
    wyniki['Wartosc k: '].append(k)
    wyniki['score'].append(np.mean(acc))
print(wyniki)


#! Regresja
# Zadanie 1
X,y= datasets.make_regression(
    n_samples=100,
    n_features=2,
    n_informative=1,
    noise=0,
    random_state=3
)

# Zadanie 3
regzad3 = KNN(7)
regzad3.fit(X,y)
X_r = regzad3.predict_regression(X)
plt.scatter(X[:, 0], X[:, 1], c='blue', label='Dane uczace')
plt.scatter(X[:, 0], X_r, c='orange', label='Predykcja')
plt.title('Zmienne niezależne')
plt.legend()
plt.show()
#Linia trendu
plt.scatter(X[:,0],X[:,0],c='blue', label='Dane uczace')
plt.scatter(X[:,1],X_r,c='orange', label='Predykcja')
plt.title("Linia trendu")
plt.legend()
plt.show()
regzad3.score_reg(X,y)

# Zadanie 4 i 5
california = datasets.fetch_california_housing()
X = california.data[0:1001]
y = california.target[0:1001]
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1)
wyniki = {'Iteracja: ':[], 'score':[]}
for i in range(1,6):
    acc = []
    for k in range(10):
        reg = KNN(i)
        reg.fit(X_train,y_train)
        reg.predict_regression(X_test)
        acc.append(reg.score_reg(X_test,y_test))
    wyniki['Iteracja: '].append(i)
    wyniki['score'].append(round(np.mean(acc),4))
print(wyniki)
        