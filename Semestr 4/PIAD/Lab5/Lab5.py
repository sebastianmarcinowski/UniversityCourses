import numpy as np
import scipy as sp
import scipy.sparse
import matplotlib.pyplot as plt
import pandas as pd

# Zadanie 1
def freq(x, prob=True,wypisz = True):
    xi = set(x)
    ni = {}
    for i in x:
        if i in ni:
            ni[i] +=1
        else:
            ni[i] = 1

    pi = {}
    for i in ni:
        pi[i] = ni[i]/len(x)
    
    if prob==True:
        if (wypisz==True):
            print("Unikalne wartosci xi")
            print(xi)
            print("Prawdopodobienstwo wystepowania kazdej z tych wartosci")
            print(pi)
        return xi,pi
    else:
        if (wypisz==True):
            print("Unikalne wartosci xi")
            print(xi)
            print("Czestosc wystepowania tych wartosci")
            print(ni)
        return xi,ni
x = [7,7,3,3,8,3,8,8,9,7,8,4,5,3,7,5,1,6,4,4,7,2,1,1,9,3,5,6,1,9,1,1,2,9,6,4,4,7,4,6,9,6,4,9,5,6,9,8,2,3]
x = [1,3,4,5,6,7,8,9]
freq(x, False)

# Zadanie 2
def freq2(x,y,prob=True,wypisz = True):
    df = pd.DataFrame({"x" : x, "y" : y})
    xyi = df.drop_duplicates()
    xi = xyi['x'].to_list()
    yi = xyi['y'].to_list()
    # print(xi)
    # print(yi)
    ni = df.value_counts(['x','y'])
    pi = {}
    for i in range(len(ni)):
        pi[ni.keys()[i]] = ni.values[i]/len(df)
    
    if prob==True:
        if (wypisz==True):
            print("Unikalne pary wartosci xi")
            print(xi)
            print("Unikalne pary wartosci yi")
            print(yi)
            print("Prawdopodobienstwo wystepowania kazdej z par wartosci")
            print(pi)
        return xi, yi ,pi
    else:
        if (wypisz==True):
            print("Unikalne pary wartosci xi")
            print(xi)
            print("Unikalne pary wartosci yi")
            print(yi)
            print("Czestosc wystepowania par tych wartosci")
            print(ni)
        return xi, yi ,ni
    
x = [10,20,30,40,50,10,20,30,35]
y = ['a','b','b','c','d','a','b','e','e']
freq2(x,y,True)

# Zadanie 3
def entropy(x, wypisz = True):
    pi = tuple(freq(x, True,wypisz)[1].values()) #konwersja z dict_values na liste
    h = 0.0
    for i in range(len(pi)):
        h = h + pi[i] * np.log2(pi[i])
    h = h * (-1)
    return h

def entropy2(x,y, wypisz = True):
    pi = tuple(freq2(x,y,True, wypisz)[2].values()) #konwersja z dict_values na liste
    h = 0.0
    for i in range(len(pi)):
        h = h + pi[i] * np.log2(pi[i])
    h = h * (-1)
    return h


def infogain(x,y, wypisz = True):
    i = entropy(x, wypisz) + entropy(y, wypisz) - entropy2(x,y, wypisz)
    return i

w = [1,5,7,5,2]
z = ['a','a','a','b','b']
print(entropy(w))
print(infogain(w,z))

# Zadanie 4
plik = pd.read_csv("Lab5/zoo.csv")
kolumna = []
entropia = []
przyrost = []
result = pd.DataFrame({})
for i in range(1,len(plik.columns)-1):
    x = plik['type']
    k = plik.columns[i]
    y = plik[k]
    kolumna.append(k)
    entropia.append(entropy(y,False))
    przyrost.append(infogain(x,y,False))
result['kolumna'] = kolumna
result['entropy'] = entropia
result['infogain'] = przyrost
result = result.sort_values(by='infogain',ascending=False)
print(result)