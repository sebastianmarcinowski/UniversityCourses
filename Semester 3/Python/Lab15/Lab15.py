import numpy as np
import scipy as sp

# Zadanie 1
def zad1():
    x=np.loadtxt(fname='I:\Python\Lab15\irisP.txt', dtype=str,comments=[":"], delimiter=",",usecols=(3))
    nazwa = np.loadtxt(fname='I:\Python\Lab15\irisP.txt', dtype=str,comments=[":"], delimiter=",",usecols=(4))
    d1=[]
    d2=[]
    d3=[]
    for i in range(len(nazwa)):
        if(nazwa[i]=='Iris-setosa'):
           d1.append(float(x[i])) 
        elif(nazwa[i]=='Iris-versicolor'):
            d2.append(float(x[i]))
        else:
            d3.append(float(x[i]))
    print("Dla iris-setosa srednia dlugosc to: " + str((sum(d1)/len(d1))))
    print("Dla iris-versicolor srednia dlugosc to: " + str((sum(d2)/len(d2))))
    print("Dla iris-virginica srednia dlugosc to: " + str((sum(d3)/len(d3))))
# zad1()
    
# Zadanie 2
def zad2():
    s = np.genfromtxt(fname="I:\Python\Lab15\irisP2.txt",dtype=float,skip_header=1,delimiter=",",usecols=(2),missing_values='?',filling_values=100)
    nazwa = np.loadtxt(fname='I:\Python\Lab15\irisP2.txt', dtype=str,comments=[":"], delimiter=",",usecols=(4))
    d1=[]
    d2=[]
    d3=[]
    for i in range(len(nazwa)):
        if(nazwa[i]=='Iris-setosa' and s[1]!=100):
           d1.append(s[i]) 
        elif(nazwa[i]=='Iris-versicolor' and s[i]!=100):
            d2.append(s[i])
        elif(nazwa[i]=='Iris-virginica' and s[i]!=100):
            d3.append(s[i])
    for i in range(len(nazwa)):
        if(nazwa[i]=='Iris-setosa' and s[i] == 100):
           s[i] = sum(d1)/len(d1)
        elif(nazwa[i]=='Iris-versicolor' and s[i]==100):
            s[i] = sum(d2)/len(d2)
        elif(nazwa[i] == 'Iris-virginica' and s[i]==100):
            s[i] = sum(d3)/len(d3)
    print(s)
# zad2()
    
# Zadanie 3
def zad3():
    x = np.loadtxt(fname='I:\Python\Lab15\contact-lenses.txt', dtype=str,comments=[":"], delimiter=",",usecols=(0,1,2,3,4))
    # print(x)
    x=np.char.upper(x)
    x=np.char.replace(x,"NO","FALSE")
    x=np.char.replace(x,"YES","TRUE")
    # print(x)
    np.savetxt(fname='contact-lenses-res.txt',X=x)
zad3()

# Zadanie 4
def zad4():
    x = np.loadtxt(fname='I:\Python\Lab15\irisP.txt', dtype=str,comments=[":"], delimiter=",",usecols=(4))
    x = np.char.lstrip(x, chars="Iris-")
    print(x)
# zad4()