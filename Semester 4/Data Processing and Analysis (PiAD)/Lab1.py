import numpy as np

# Zadania podsumowujące
# Zadanie 1
a = np.random.randint(1000,size=(10,5))
print(np.trace(a)) #suma elementow przekatnej
print(np.diag(a)) #elementy lezace na przekatnej 

# Zadanie 2
b1 = np.random.normal(size=10)
b2 = np.random.normal(size=10)
print(np.multiply(b1,b2)) #mnozenie komorka na komorke
print(b1)
print(b2)
b1 = np.reshape(b1,10)
print(b1@b2) #mnozenie macierzowe

# Zadanie 3
c1 = np.random.randint(1,100,100).reshape(20,5)
c2 = np.random.randint(1,100,100).reshape(20,5)
print(np.add(c1,c2))

# Zadanie 4
d1 = np.random.randint(1,100,size=(5,4))
d2 = np.random.randint(1,100,size=(4,5))
d2 = np.transpose(d2)
print(np.add(d1, d2))
print(d1)
print(d2)

# Zadanie 5 ->korzysta z macierzy z zadania 4
print(d1[:,2:4]*d2[:,2:4])

# Zadanie 6
e1 = np.random.normal(size=(5,5))
e2 = np.random.uniform(size=(5,5))
print("Dane dla macierzy o rozkladzie normalnym")
print(np.min(e1))
print(np.max(e1))
print(np.sum(e1))
print(np.std(e1))
print(np.mean(e1))
print(np.var(e1))
print("Dane dla macierzy o rozkladzie jednostajnym")
print(np.min(e2))
print(np.max(e2))
print(np.sum(e2))
print(np.std(e2))
print(np.mean(e2))
print(np.var(e2))

# Zadanie 7
a = np.random.normal(size=(5,5))
b = np.random.normal(size=(5,5))
print(a*b)
print(np.dot(a,b))

# Zadanie 8
f = np.random.randint(1,100,size=(10,10))
print(f)
print(np.lib.stride_tricks.as_strided(f[:3,:],shape=(3,5),strides=(f.strides[0],f.strides[1]*2)))
# linia wybierze z macierzy f 3 pierwsze wiersze z co drugiej kolumny
# f.strides[0] -> przesunie sie na nowy wierszy w pierwszej kolumnie
# f.strides[1] -> przesunie sie o jeden element tablicy

# Zadanie 9
a = np.arange(1,40,4)
b = np.arange(40,0,-4)
print(a)
print(b)
print(np.vstack((a,b)))
print(np.hstack((a,b)))

# Zadanie 10
a = np.arange(0,24,1).reshape(4,6)
print(a)
print(np.max(np.lib.stride_tricks.as_strided(a,shape=(2,3),strides=(a.strides[0],a.strides[1])))) #blok koloru zoltego
print(np.max(np.lib.stride_tricks.as_strided(a[:,3],shape=(2,3),strides=(a.strides[0],a.strides[1])))) #blok koloru zielonego
print(np.max(np.lib.stride_tricks.as_strided(a[2:],shape=(2,3),strides=(a.strides[0],a.strides[1])))) #blok koloru niebieskiego
print(np.max(np.lib.stride_tricks.as_strided(a[2:,3:],shape=(2,3),strides=(a.strides[0],a.strides[1])))) #blok koloru pomaranczowego