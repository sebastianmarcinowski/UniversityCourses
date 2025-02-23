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

    @property
    def imie(self):
        return self.__imie
    @property
    def nazwisko(self):
        return self.__nazwisko
    @property
    def pesel(self):
        return self.__pesel
    @property
    def wzrost(self):
        return self.__wzrost
    @wzrost.setter
    def wzrost(self, value):
        if(value < 0):
            self.__wzrost = 0
        else:
            self.__wzrost = value
    @property
    def waga(self):
        return self.__waga
    @waga.setter
    def waga(self, value):
        if(value < 0):
            self.__waga = 0
        else:
            self.__waga = value


    def __del__(self):
        Osoba.__ilosc -= 1
    
    def __hash__(self):
        return int(self.__pesel)

    def __str__(self):
        return "PESEL: " + self.__pesel + " Imie: " + self.__imie + " Nazwisko: " + self.__nazwisko

    def __repr__(self):
        return "Osoba (" + repr(self.__pesel) + "," + repr(self.__imie) + "," + repr(self.__nazwisko) + "," + repr(self.__wzrost) + "," + repr(self.__waga) + "," + repr(self.__rokurodzenia) + ")"

    # def getWaga(self):
    #     return(self.__waga)

    # def setWaga(self,waga):
    #     self.__waga = waga

    # def getWzrost(self):
    #     return (self.__wzrost)

    # def setWzrost(self,wzrost):
    #     self.__wzrost = wzrost
    @property
    def wiek(self):
        teraz = time.localtime()
        return teraz.tm_year - self.__rokurodzenia
    
    @staticmethod
    def liczbaInstancji():
        return Osoba.__ilosc
    
    @classmethod
    def konstruktor(cls,pesel,imie,nazwisko,wzrost,waga):
        return cls(pesel,imie,nazwisko,wzrost/100,waga)
    

class Pracownik(Osoba):
    def __init__(self,  pesel, imie, nazwisko, mPracy, pensja,wzrost=0.0, waga=0.0,):
        super().__init__( pesel, imie, nazwisko, wzrost, waga)
        self.__mPracy = str(mPracy)
        self.__pensja = float(pensja)

    @property
    def mPracy(self):
        return self.__mPracy
    @mPracy.setter
    def mPracy(self, value):
        self.__mPracy = value

    @property
    def pensja(self):
        return self.__pensja
    @pensja.setter
    def pensja(self, value):
        if(value < 0):
            self.__pensja = 0
        else:
            self.__pensja = value

    def __str__(self):
        return super().__str__() + " " + "Miejsce zatrudnienia: " + self.__mPracy + " Pensja: " + str(self.__pensja)

    def __repr__(self):
        return super().__repr__() + " " + repr(self.__mPracy) + "," + repr(self.__pensja)

# Zadanie 2 
# pracownik = Pracownik(12345678912,"Marek","Marucha","Piekarnia", 2500.35, 190.1, 95.6)
# print(Pracownik.__str__(pracownik))


# Zadanie 3
baza = [Osoba("12345678912","Adam", "Kowalski", 186, 77.3),
           Osoba("12345678912","Adam", "Kowalski", 186, 77.3),
           Osoba("12345678912","Adam", "Kowalski", 186, 77.3),
           Osoba("12345678912","Adam", "Kowalski", 186, 77.3),
           Osoba("12345678912","Adam", "Kowalski", 186, 77.3),
           Pracownik(12345678912,"Marek","Marucha","Piekarnia", 2500.35, 190.1, 95.6),
           Pracownik(12345678912,"Marek","Marucha","Piekarnia", 2500.35, 190.1, 95.6),
           Pracownik(12345678912,"Marek","Marucha","Piekarnia", 2500.35, 190.1, 95.6)]
for obj in baza:
    print(obj.__repr__())
    print("----------------")