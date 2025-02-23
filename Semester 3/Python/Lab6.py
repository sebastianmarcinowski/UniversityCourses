from base64 import *
# Zadanie 1
# t = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. In tempus massa nec purus auctor facilisis. Nulla facilisi. Ut interdum metus quis purus tempus, ac maximus mi rutrum. Quisque sed pretium lectus, et scelerisque sapien. Vivamus cursus et odio et cursus. Pellentesque at velit massa. Fusce pharetra diam ut quam ultricies euismod. Etiam sed porttitor mauris. Duis vel fermentum dolor. Integer molestie ipsum at vestibulum ultricies. In hac habitasse platea dictumst. Cras eu urna ligula. Nulla ac odio velit. Nullam efficitur nulla id dui mollis luctus. Phasellus a bibendum ante, at interdum ligula. Sed nulla ante, porttitor ac consectetur at, tempus et felis."
# t = set(t.lower().replace(',','').replace('.','').split())
# print(len(t))

# Zadanie 2
# a = {1,2,3,4,5}
# b = {2,4,5}
# print(a.issubset(b)) #sprawdzanie czy jest podzbiorem
# print(a.issuperset(b)) #sprawdzanie czy jest nadzbiorem
# print (a.intersection(b)) #czesc wspolna (przeciecie zbiorow)
# print(a.symmetric_difference(b)) #roznica symetryczna
# print(a.difference(b)) #roznica
# print(a.union(b)) #suma zbiorow

# Zadanie 3
# a = {1,2,3,4,5}
# b = {2,4,5}
# x = [list([i,j]) for i in a for j in b]
# print (x)

# Zadanie 4
# x = {
#     1:"jeden",
#     2:"dwa",
#     3:"trzy",
#     4:"cztery",
#     5:"piec",
#     6:"szesc",
#     7:"siedem",
#     8:"osiem",
#     9:"dziewiec",
#     10:"dziesiec",
#     11:"jedenascie",
#     12:"dwanascie",
#     13:"trzynascie",
#     14:"czternascie",
#     15:"pietnascie",
#     16:"szesnascie",
#     17:"siedemnascie",
#     18:"osiemnascie",
#     19:"dziewietnascie",
#     20:"dwadziescia",
#     30:"trzydziesci",
#     40:"czterdziesci",
#     50:"piecdziesiat",
#     60:"szescdziesiat",
#     70:"siedemdziesiat",
#     80:"osiemdziesiat",
#     90:"dziewiecdziesiat"
# }
# liczba = int(input("Podaj liczba z zakresu <1,99>: "))
# if(liczba>0 and liczba<100):
#     if(liczba>0 and liczba<10):
#         print(x[liczba%10])
#     elif(liczba<10 and liczba>20):
#         print(x[liczba])
#     else:
#         print(x[(int(liczba/10))*10] + " " + x[liczba%10])

# Zadanie 5
base64Table = dict()
for i in range(26):
    base64Table[i] = chr(65 + i)
for i in range(26):
    base64Table[i + 26] = chr(97 + i)
for i in range(10):
    base64Table[i + 26*2] = chr(48 + i)
base64Table[62] = '+'
base64Table[63] = '/'
