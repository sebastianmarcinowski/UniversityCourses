from collections import *
from random import *
# Zadanie 1
# napis = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis vel mattis tortor. Vivamus non mattis nulla, sed vestibulum velit. Donec tempus ligula leo, ac aliquam mauris feugiat bibendum. Pellentesque tempus id turpis vitae pharetra. Sed ut eleifend metus, placerat elementum lectus. Aliquam erat volutpat. Quisque nulla dui, euismod non nisi id, mollis euismod erat. Sed vitae feugiat nunc, vel vehicula nunc. Integer tempor massa et eros iaculis auctor. Donec iaculis bibendum lectus, a hendrerit mauris. Pellentesque lectus diam, suscipit in metus ut, pharetra porttitor lectus. Nunc condimentum nisi et diam malesuada pretium."
# napis = napis.lower().replace(".", " ").replace(","," ").split(" ")
# print(Counter(napis))

# Zadanie 2 jest git ale jeszcze wartosci klucza by sie przydaly
# data = [['sunny',85,85,'FALSE','no'], \
# ['sunny',80,90,'TRUE','no'], \
# ['overcast',83,86,'FALSE','yes'], \
# ['rainy',70,96,'FALSE','yes'], \
# ['rainy',68,80,'FALSE','yes'], \
# ['rainy',65,70,'TRUE','no'], \
# ['overcast',64,65,'TRUE','yes'], \
# ['sunny',72,95,'FALSE','no'], \
# ['sunny',69,70,'FALSE','yes'], \
# ['rainy',75,80,'FALSE','yes'], \
# ['sunny',75,70,'TRUE','yes'],
# ['overcast',72,90,'TRUE','yes'], \
# ['overcast',81,75,'FALSE','yes'], \
# ['rainy',71,91,'TRUE','no']]
# data_tranpose =  list(zip(*data))
# g = Counter(data_tranpose)
# z = []
# for i in g:
#     d=[]
#     x = Counter(i)
#     for j in x.values():
#         d.append(round(j/14,2))
#     z.append(d)
# print(z)

# Zadanie 2 - poprawnie 
# p = []
# for r in data_tranpose:
#     p.append(Counter(r))
#     for key in p[-1]:
#         p[-1][key] /= len(r)
#         p[-1][key] = round(p[-1][key],2)
#     print(p[-1])


# Zadanie 3
# wersja A - cos nie dziala
# p = sorted(p, key = lambda x:p[2])
# print(p)

# wersja B
# for i in range(len(p)):
#     p[i] =OrderedDict(sorted(p[i].items(), key = lambda x:x[1]))
#     print(p[i])


# Zadanie 4
# dd = defaultdict(lambda : 5)
# for i in range(5):
#     x = int(input("Podaj: "))
#     dd[x] += 1
# print(dd)

# Zadanie 5
# def palindrom(str):
#     test = True
#     str =str.lower().replace(" ","")
#     pal = deque(str)
#     for i in range(0, len(str)//2):
#         if(pal.pop()!=pal.popleft()):
#             test = False
#     if(test==True):
#         print("Palindrom")
#     else:
#         print("Nie palindrom")

# str = "qwertyuioppoiuytrewq"
# palindrom(str)
