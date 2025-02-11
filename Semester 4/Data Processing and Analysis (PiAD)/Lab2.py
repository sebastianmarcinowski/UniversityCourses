import numpy as np
import scipy
import scipy.stats
import matplotlib.pyplot as plt
import pandas as pd
import random
import sys as os
df = pd.DataFrame({"x": [1,2,3,4,5], "y":['a','b','a','b','b']})

# Zadanie 1
print(df.groupby('y').mean('x'))

# Zadanie 2
print(df.value_counts('y'))

# Zadanie 3
plik = np.loadtxt(fname='C:/Users/smh2k/Desktop/PIAD/Lab2/autos.csv',dtype=str,comments=[":"], delimiter=",")
plik2 = pd.read_csv('C:/Users/smh2k/Desktop/PIAD/Lab2/autos.csv')
print(plik)
print(plik2)
# Roznica polega na sposobie wyswietlania danych

# Zadanie 4
srednie_zuzycie = plik2[['make','city-mpg','highway-mpg']].groupby('make').mean(['city-mpg','highway-mpg'])
srednia_paliwa = (srednie_zuzycie['city-mpg'].values + srednie_zuzycie['highway-mpg'].values)/2
srednie_zuzycie['srednia'] = srednia_paliwa
print(srednie_zuzycie)

# Zadanie 5
typ_paliwa = plik2.value_counts(['make','fuel-type'])
print(typ_paliwa)

# Zadanie 6
cmpg = plik2['city-mpg'].values
length = plik2['length'].values
w1 = np.polyfit(length,cmpg,1)
w2 = np.polyfit(length,cmpg,2)
print(w1)
print(w2)

# Zadanie 7
korelacja = scipy.stats.pearsonr(length,cmpg)
print(korelacja)
#! statistic to wspolczynnik korelacji 

# Zadanie 8
plt.plot(length,cmpg, 'ro', label='city-mpg')
plt.plot(length,np.polyval(w1,length), label='linear polynomial of best fit')
plt.legend()
plt.show()

# Zadanie 9 
f = scipy.stats.gaussian_kde(length)
wartosci = np.linspace(length.min(), length.max(),len(length))
ax = plt.subplot(2,1,1)
plt.title("Wykres dla zmiennej length")
ax.plot(length,f.evaluate(length), 'bo', label='Próbki')
ax.plot(wartosci,f.evaluate(wartosci),'r', label='Estymator Gaussa')

# Zadanie 10
width = plik2['width'].values
f2 = scipy.stats.gaussian_kde(width)
wartosci2 = np.linspace(width.min(), width.max(),len(width))
bx = plt.subplot(2,1,2)
plt.title("Wykres dla zmiennej width")
bx.plot(width,f2.evaluate(width), 'bo', label='Próbki')
bx.plot(wartosci2,f2.evaluate(wartosci2),'r', label='Estymator Gaussa')
plt.legend()
plt.show()