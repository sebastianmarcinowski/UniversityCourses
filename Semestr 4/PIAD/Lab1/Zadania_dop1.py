import numpy as np

# Zadania dopełniające

# tablice
# a=np.array([1,2,3,4,5,6,7])
# b=np.array([[1,2,3,4,5],[6,7,8,9,10]])
# b=b.transpose()
# print(b)
# tab1 = np.arange(100)
# print(tab1)
# tab2 = np.linspace(0,2,10)
# print(tab2)
# tab3 = np.arange(0,100,5)
# print(tab3)

#liczby losowe
# a = np.random.normal(3,2,size=(1,20))
# a = np.round(a,2)
# print(a)
# b = np.random.randint(1,1000,size=(1,100))
# print(b)
# c1 = np.zeros((3,2))
# c2 = np.ones((3,2))
# print(c1)
# print(c2)
# d = np.random.randint(100,size=(5,5))
# d=d.astype('4byte')
# print(d)
# e = np.random.random(10)*10
# print(e)
# e=e.astype('int')
# print(e)
# e = np.ceil(e)
# print(e)
# e = e.astype(int)
# print(e)

# Selekcja danych
# b = np.array([[1,2,3,4,5],[6,7,8,9,10]],dtype=np.int32)
# print(np.ndim(b))
# print(np.size(b))
# print(b[0,1],b[0,3])
# print(b[0,:])
# print(b[:,0])
# c = np.random.randint(0,100,size=(20,7))
# print(c[:,0:4])

# Operacje matematyczne i logiczne
# a= np.random.randint(0,10,size=(3,3))
# b= np.random.randint(0,10,size=(3,3))
# print(a)
# print(b)
# c = a+b
# d1 = a*b #mnozenie komorka przez komorke
# d2 = np.multiply(a,b) #mnozenie macierzowe
# e1 = np.divide(a,b) #dzielenie macierzowe
# e2 = a/b #dzielenie komorka przez komorke
# f = np.power(a,b)
# print(a[a>=4]) #wypisanie wartosci ktore są >=4
# print(a[(a>1) & (a<4)])
# print(np.trace(a)) #suma elementow diagonali

# Dane statystyczne #macierze sa z poprzednich zadan
# print(np.min(b))
# print(np.max(b))
# print(np.sum(b))
# print(np.std(b)) #odchylenie standardowe

# Rzutowanie wymiarów za pomoca shape i resize
# a = np.array(np.random.randint(500,size=50))
# zmiana wymiarów tablicy
# a2 = np.reshape(a,(10,5))
# a3 = np.resize(a,(10,5))
# a4 = np.ravel(a2) #"spłaszcza wymiary podanej tablicy"
# b1 = np.random.randint(0,100,size=5)
# b2 = np.random.randint(0,100,size=4)
# b3 = b1+b2 #tutaj wyrzuca blad dotyczacy roznicy w wymiarach tablic
# b2 = b2[:,np.newaxis] #newaxis powieksza dany wymiar tablicy o 1
# b3 = b1 + b2 
# print(b3)

# Sortowanie danych
a = np.random.randn(5,5)
print(a)
print(np.sort(a,axis=-0)) #axis=0 sortuje kolumnami, axis=1 sortuje wierszami
print(np.sort(a,axis=1))
