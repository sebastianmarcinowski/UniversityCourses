import numpy as np
import scipy as sp
import scipy.sparse
import matplotlib.pyplot as plt
import pandas as pd
from sklearn import datasets
from sklearn.decomposition import PCA


def wiPCA(data, x):
    # Wyznaczanie srednich dla wierszy
    srednia = np.mean(data, axis=0)
    data = data - srednia
    # Macierz kowariancji oraz jej wektory i wartosci wlasne
    macierz_kowariancji = np.cov(data.T)
    # Wartosci wlasne i wektory wlasnie
    wartosci, wektory = np.linalg.eig(macierz_kowariancji)
    # Sortowanie i 'ucinanie'
    id = wartosci.argsort()[::-1]
    wektory=wektory[:,id]
    w = wektory[:,:x]
    pca_data = np.dot(data,w)
    return pca_data,wartosci[id],wektory,srednia
def odwPCA(data,vec,x):
    org_data = data[:,:x].dot(vec[:,:x].T)
    return org_data
# Zadanie 1
def wektory_wykres(val,vec,srednia,x):
    wartosc=3*np.sqrt(val)
    srednia=np.array([srednia]).T
    z=srednia+vec
    wektory=wartosc*(z-srednia)
    return wektory[:x,:x]
# Moje PCA
data=np.dot(np.random.randn(2,2), np.random.randn(2,200)).T
pca_data,val,vec,srednia = wiPCA(data,1)
pca_data = odwPCA(pca_data,vec,1)
# Wbudowane PCA
pca=PCA(n_components=2)
X_r = pca.fit(data).transform(data)
# Wykres
wektory = wektory_wykres(val,vec,srednia,2) 
v1 = wektory[:,0]
print(v1)
v2 = wektory[:,1]
plt.scatter(data[:,0],data[:,1])
plt.scatter(-pca_data[:,0],-pca_data[:,1],color='orange')
plt.arrow(x=srednia[0],y=srednia[1],dx=v1[0],dy = v1[1],width=0.03,color='black')
plt.arrow(x=srednia[0],y=srednia[1],dx=v2[0],dy = v2[1],width=0.03,color='black')
plt.show()

# Zadanie 2
iris = datasets.load_iris()
data = iris.data
pca_data,val,vec,srednia = wiPCA(data,2)
wykres=plt.scatter(pca_data[:,0],-pca_data[:,1],c=iris.target)
plt.title('Zadanie 2 - iris')
plt.legend(handles=wykres.legend_elements()[0], labels=iris.target_names.tolist())
plt.show()

# Zadanie 3
digits = datasets.load_digits()
data = digits.data
pca_data,val,vec,srednia = wiPCA(data,2)
odw_pca_data = odwPCA(pca_data,vec,2)
wykres=plt.scatter(-pca_data[:,0],-pca_data[:,1],c=digits.target)
plt.title('Zadanie 3 - digits')
plt.colorbar()
plt.show()
# Wariancja
wariancja = val/sum(val)
wariancja = wariancja.cumsum()
plt.plot(np.arange(len(wariancja)),wariancja)
plt.title("Krzywa wariancji")
plt.show()
# Średni błąd rekonstrukcji
blad = pd.DataFrame(columns=['Wymiar','Srednia'])
for i in range(len(vec)):
    pca_data,val,vec,srednia = wiPCA(data,i)
    odw_pca_data = odwPCA(pca_data,vec,i)
    odleglosc = np.sqrt(np.sum((data-odw_pca_data)**2,axis=0))
    blad = blad._append({'Wymiar':i,'Srednia':odleglosc.mean()},ignore_index=True)
plt.plot(blad['Wymiar'],blad['Srednia'],color='green')
plt.title("Średni błąd rekonstrukcji")
plt.show()