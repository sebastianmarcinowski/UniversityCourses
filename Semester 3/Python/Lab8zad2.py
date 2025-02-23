import time
class Osoba:
    __ilosc =0
    def __init__(self, pesel, imie, nazwisko, wzrost=0.0, waga=0.0):
        self.__imie = str(imie)
        self.__nazwisko = str(nazwisko)
        self.__pesel = str(pesel)
        self.__wzrost = float(wzrost)
        self.__waga = float(waga)
        if(int(self.__pesel[2:4])>12):
            self.__rokurodzenia = 2000 + int(self.__pesel[:2])
        else:
            self.__rokurodzenia = 1900 + int(self.__pesel[:2])
        Osoba.__ilosc +=1

    def __del__(self):
        Osoba.__ilosc -= 1
    
    def __hash__(self):
        return int(self.__pesel)

    def __str__(self):
        return "PESEL: " + self.__pesel + " Imie: " + self.__imie + " Nazwisko: " + self.__nazwisko

    def __repr__(self):
        return "Osoba (" + repr(self.__pesel) + "," + repr(self.__imie) + "," + repr(self.__nazwisko) + "," + repr(self.__wzrost) + "," + repr(self.__waga) + "," + repr(self.__rokurodzenia) + ")"

    def getWaga(self):
        return(self.__waga)

    def setWaga(self,waga):
        self.__waga = waga

    def getWzrost(self):
        return (self.__wzrost)

    def setWzrost(self,wzrost):
        self.__wzrost = wzrost

    def wiek(self):
        teraz = time.localtime()
        return teraz.tm_year - self.__rokurodzenia
    
    @staticmethod
    def liczbaInstancji():
        return Osoba.__ilosc
    
    @classmethod
    def konstruktor(cls,pesel,imie,nazwisko,wzrost,waga):
        return cls(pesel,imie,nazwisko,wzrost/100,waga)


osoba = Osoba(12345678912,"Marek","Marucha", 190.1, 95.6)
# print(osoba._Osoba__imie)
# print(osoba._Osoba__nazwisko)
# print(osoba._Osoba__pesel)
# print(osoba._Osoba__wzrost)
# print(osoba._Osoba__waga)
# print(osoba._Osoba__rokurodzenia)
# print(Osoba.__repr__(osoba))
print(Osoba.konstruktor("12345678912","Adam", "Kowalski", 186, 77.3))
