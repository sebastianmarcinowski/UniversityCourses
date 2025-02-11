import math

def ulamek(x):
    return round(1/x,6)

def pierwiastek(x):
    return round(math.sqrt(x),6)

def potega2(x):
    return x**2

def modulo(x,b):
    return x%b

def ln(x):
    return round(math.log(x,math.exp(1)),6)

def loga10(x):
    return round(math.log10(x),6)

def silnia(x):
    if x > 1:
        return x*silnia(x-1)
    return 1

def potegaxy(x,y):
    return round(x**y,2)

def potega10(x):
    return 10**x

def exp(x):
    return round(math.exp(x),6)