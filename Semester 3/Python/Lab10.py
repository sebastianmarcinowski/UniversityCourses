import time
# Zadanie 1
# class Potegi2:
#     def __init__(self, a, b=0):
#         self.a = a
#         self.b =b

#     def __call__(self):
#         self.b +=1
#         return self.a**self.b
# x = Potegi2(2)    
# potega = int(input("Podaj liczbe poteg liczby 2: "))
# for i in range(potega):
#     print(x(2,i))

# Zadanie 2
# class Potega():
#     def __init__(self, podstawa, maks, min=0):
#         self.podstawa = podstawa
#         self.min = min
#         self.maks = maks

#     def __iter__(self):
#         return self
    
#     def __next__(self):
#         if(self.min > self.maks):
#             raise StopIteration
#         else:
#             self.min +=1
#         return self.podstawa**self.min

# def PotegaGen(podstawa, maks, min):
#     while min<=maks:
#         yield podstawa ** min
#         min+=1

# for i in Potega(2,10,0):
#     print(i)
    # time.sleep(1)

# for i in PotegaGen(2,10,0):
    # print(i)


# Zadanie 3
class Lista:
    class Element:
        def __init__(self,value,next=None,prev=None):
            self.__value = value
            self.next = None
            self.prev = None

        @property
        def value(self):
            return self.__value
        

    def __init__(self, args):
        self.__root = None
        self.__end = None
        for i in args:
            self.insert(i)
    
    def insert(self, value):
        nowy = self.Element(value)
        
        if(self.__root == None):
            self.__root = nowy
            self.__end = nowy
            nowy.prev = None
            nowy.next = None
        elif(self.__root.value > nowy.value):
            nowy.next = self.__root
            nowy.prev=None
            self.__root.prev = nowy
            self.__root = nowy
        elif(nowy.value > self.__end.value):
            self.__end.next = nowy
            nowy.prev = self.__end
            self.__end = nowy
        else:
            curr = self.__root
            while(nowy.value > curr.value):
                curr = curr.next
                if(curr.value > nowy.value):
                    nowy.next = curr
                    nowy.prev = curr.prev
                    curr.prev.next = nowy
                    curr.prev = nowy

            
    def __iter__(self):
        curr  = self.__root
        while not(curr is None):
            yield curr.value 
            curr = curr.next

    def __reversed__(self):
        curr = self.__end
        while not(curr is None):
            yield curr.value
            curr = curr.prev
        # print(self.__root.value)

    def __contains__(self,value):
        curr = self.__root
        while(curr.value < value):
            curr = curr.next
        if(curr.value == value):
            return True
        else:
            return False

lista = Lista([2,3,4,5])
lista.insert(11)
lista.insert(1)
lista.insert(6)
for i in reversed(lista):
    print(i)
print("-----------------------------")
lista = Lista([8,10,9,13])
# print(11 in lista)