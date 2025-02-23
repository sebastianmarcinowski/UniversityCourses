


# Zadanie 1
# c = [0, -2, 1, 7, 3, 4]
# print(c[::-1])

# Zadanie 2
# x = float(input("Podaj wartosc x: "))
# y = float(input("Podaj wartosc y: "))
# z = float(input("Podaj wartosc z: "))
# c = float(input("Podaj wartosc c: "))

# if(c==1):
#     wynik = x+y+z
#     print(wynik)
# elif(c==2):
#     wynik = x-y-z
#     print(wynik)
# elif(c==3):
#     if(x==0 or y==0 or z==0):
#         print("Przez 0 sie nie dzieli")
#     else:
#         wynik = x/y/z
#         print(wynik)
# else:
#     print("Podano bledna wartosc c.")

# Zadanie 3 
# waga = int(input("Podaj swoja wage: "))
# wzrost = int(input("Podaj swoj wzrost: "))
# bmi = waga/(wzrost*wzrost)
# if(bmi<18.5):
#     print("Niedowaga")
# elif(18.5<=bmi<25):
#     print("Waga w normie")
# elif(25<=bmi<30):
#     print("Nadwaga")
# else:
#     print("Otylosc stopnia 1,2 lub 3")

# Zadanie 4
# x = int(input("Podaj wielkosc piramidy: "))
# for i in range(x):
#     print("x"*(i+1))

# Zadanie 5
# lista = [21, 2, 221, 122, 321, 241, 3421, 4231]
# liczba = 21
# for i in range(len(lista)):
#     if str(liczba) in str(lista[i]):
#         print(lista[i])

# Zadanie 6
# c0 = 1
# liczba = 0
# n = 0
# lista =[]
# while liczba <1000000:
#     liczba = ((4*n+2)/(n+2))*c0
#     c0=liczba
#     n = n+1
#     if(liczba%2==0):
#         lista.append(liczba)
# print(lista)

# Zadanie 7
# lista = [i for i in range(1,8,3)]
# for i in range(3):
#     print(lista)

# Zadanie 8:
c = 2
n = int(input("Podaj ilosc liczb pierwszych do znalezienia: "))
lista = []
dzielniki = []
for c in range(10000000):
    for i in range(c):
        if i>0:
            if(c%i==0):
                dzielniki.append(i)
    if(len(dzielniki)>2):
        break
    elif(len(dzielniki)==2):
        lista.append(c)
    if(len(lista)>=n):
        break
    dzielniki.clear
print(lista)