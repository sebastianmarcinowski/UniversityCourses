import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
import pandas as pd
import random

# Zadania dopelniajace

# manipulacja danymi
# id = pd.date_range('2020-01-01 00:00:00', periods=5,freq="D")
# df = pd.DataFrame(np.random.randn(5,3), index=id, columns=['A','B','C'])
# print(df)

df = pd.DataFrame(np.random.randn(20,3),index=np.arange(20), columns=['A','B','C'])
print(df)
print('3 pierwsze elementy tabeli\n',df.head(3))
print('3 ostatnie elementy tabeli\n',df.tail(3))
print('indeks tabeli\n',df.index)
print('nazwy kolumn\n',df.columns)
print('losowe wiersze\n',df.sample(5))
print('wartosci kolumny A\n', df['A'].values)
