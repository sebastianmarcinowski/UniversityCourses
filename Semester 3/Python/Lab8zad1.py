
class Ulamek:
    def __init__(self, licznik, mianownik):
        self.__licznik = licznik
        self.__mianownik = mianownik
        
    def __mul__(self, other):
        nowyM = self.__mianownik * other.__mianownik
        nowyL = self.__licznik * other.__licznik
        return Ulamek(nowyL, nowyM)

    def __add__(self, other):
        if(self.__mianownik == other.__mianownik):
            nowyM = self.__mianownik
            nowyL = self.__licznik + other.__licznik
        else:
            nowyM = self.__mianownik * other.__mianownik
            nowyL = (self.__licznik*other.__mianownik)+(self.__mianownik*other.__licznik)
        return(nowyL,nowyM)

    def __sub__(self, other):
        if(self.__mianownik == other.__mianownik):
            nowyM = self.__mianownik
            nowyL = self.__licznik - other.__licznik
        else:
            nowyM = self.__mianownik * other.__mianownik
            nowyL = (self.__licznik*other.__mianownik)-(self.__mianownik*other.__licznik)
        return(nowyL,nowyM)

    def __truediv__(self, other):
        nowyM = self.__mianownik * other.__licznik
        nowyL = self.__licznik * other.__mianownik
        return(nowyL,nowyM)

    def __str__ (self):
        return str(self.__licznik) + "/" + str(self.__mianownik)
    

ulamek1 = Ulamek(4,5)
# print(ulamek1._Ulamek__licznik)
# print(ulamek1._Ulamek__mianownik)
ulamek2 = Ulamek(7,8)
print(Ulamek.__add__(ulamek1,ulamek2))
print(Ulamek.__mul__(ulamek1,ulamek2))
print(Ulamek.__sub__(ulamek1,ulamek2))
print(Ulamek.__truediv__(ulamek1,ulamek2))
