from struct import pack, unpack
# Zadanie 1
# plik = open("zad1_1.txt")
# lines = plik.readlines()
# linie = []
# temp = plik.readline()
# while (temp != ' '):
#     linie.append(temp)
#     temp = plik.readline()

# print(linie)
# print(lines)
# plik.close()

# Zadanie 2

# def iris(nazwa):
#     plik = open(nazwa)
#     data = []
#     for i in plik.readlines():
#         data.append(i.split(',')) 
    
#     print(*data,sep="\n")
#     plik.close()
# iris("iris.txt")

# Zadanie 3
def zapis(nazwa1,nazwa2):
    plik1 = open(nazwa1, 'r')
    plik2 = open(nazwa2, "w")
    data = []
    ile =0
    for i in plik1.readlines():
        data.append(i.split(',')) 
    for l in data:
        if float(l[0])>5:
            ile+=1
            txt=''
            for elem in l:
                txt+=elem
                txt+=' '
            plik2.write(txt+"\n") 
zapis("iris.txt","zad3.txt")