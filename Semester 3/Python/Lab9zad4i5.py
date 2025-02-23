from abc import ABC, abstractmethod
import math
class Figura(ABC):
    @abstractmethod
    def obliczPole(self):
        pass

    @abstractmethod
    def typFigury(self):
        pass

    def print(self):
        print("Figura: " + self.typFigury() + ", Pole: " + str(self.obliczPole()))

class Kwadrat(Figura):
    def __init__(self, a):
        if(isinstance(a, (int,float))):
            self.a = a
        else:
            raise TypeError("Not a int or float")
    def obliczPole(self):
        return self.a**2
    
    def typFigury(self):
        return "Kwadrat"
    
class Trojkat(Figura):
    def __init__(self, a, h):
        if(isinstance(a,(int,float))):
            self.a = a
        else:
            raise TypeError
        if(isinstance(a,(int,float))):
            self.h = h
        else:
            raise TypeError
    def obliczPole(self):
        return (self.a*self.h)/2
    
    def typFigury(self):
        return "Trojkat"
    
class Kolo(Figura):
    def __init__(self, r):
        if(isinstance(r,(int,float))):
            self.r = r
        else:
            raise TypeError
    def obliczPole(self):
        return math.pi*(self.r**2)
    
    def typFigury(self):
        return "Kolo"

# Zadanie 4  
kolo = Kolo(5)
kwadrat = Kwadrat(5)
trojkat = Trojkat(5,3)
kolo.print()
kwadrat.print()
trojkat.print()

