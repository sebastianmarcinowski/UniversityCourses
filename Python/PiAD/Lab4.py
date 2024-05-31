import numpy as np
import matplotlib.pyplot as plt
import pylab as py
from skimage import data
from skimage import filters
from skimage import exposure
from PIL import Image
import matplotlib.image

#! Dyskretyzacja
# Zadanie 1,2,3
def sinus(f,fs):
    # f-czestotliwosc sygnalu, fs-czestotliwosc probkowania
    czas = np.arange(0,1,(1/fs))
    s  =[]
    for i in range(len(czas)):
        s.append(np.sin(2*np.pi*f*czas[i]))
    return czas,s

plt.subplot(2,5,1)
plt.plot(sinus(10,20)[0],sinus(10,20)[1])
plt.title('f = 10Hz, Fs = 20Hz')
plt.subplot(2,5,2)
plt.plot(sinus(10,21)[0],sinus(10,21)[1])
plt.title('f = 10Hz, Fs = 21Hz')
plt.subplot(2,5,3)
plt.plot(sinus(10,30)[0],sinus(10,30)[1])
plt.title('f = 10Hz, Fs = 30Hz')
plt.subplot(2,5,4)
plt.plot(sinus(10,45)[0],sinus(10,45)[1])
plt.title('f = 10Hz, Fs = 45Hz')
plt.subplot(2,5,5)
plt.plot(sinus(10,50)[0],sinus(10,50)[1])
plt.title('f = 10Hz, Fs = 20Hz')
plt.subplot(2,5,6)
plt.plot(sinus(10,100)[0],sinus(10,100)[1])
plt.title('f = 10Hz, Fs = 100Hz')
plt.subplot(2,5,7)
plt.plot(sinus(10,150)[0],sinus(10,150)[1])
plt.title('f = 10Hz, Fs = 150Hz')
plt.subplot(2,5,8)
plt.plot(sinus(10,200)[0],sinus(10,200)[1])
plt.title('f = 10Hz, Fs = 200Hz')
plt.subplot(2,5,9)
plt.plot(sinus(10,250)[0],sinus(10,250)[1])
plt.title('f = 10Hz, Fs = 250Hz')
plt.subplot(2,5,10)
plt.plot(sinus(10,1000)[0],sinus(10,1000)[1])
plt.title('f = 10Hz, Fs = 1000Hz')
plt.show()

# Zadanie 4
# Twierdzenie Nyquista-Shannona - twierdzenie określające częstotliwość próbkowanie, aby wiernie odtworzyć sygnał mówi ono, 
# że aby sygnał mógł zostać jednoznacznie odtworzony to częstotliwość próbkowania musi być przynajmniej 2 razy większa od częstotliwości sygnału

# Zadanie 5
# Aliasing - nieodwracalne zniekształcenie sygnału w procesie próbkowania

# Zadanie 6,7
obraz = plt.imread("C:/Users/smh2k/Desktop/PIAD/Lab4/robal.png")
plt.imshow(obraz)

plt.ylim(200,300)
plt.xlim(230,300)
plt.axis((200,300,230,300))
#? axis i ylim+xlim daja podobne efekty

plt.title("imshow()")
plt.matshow(obraz)
plt.title("matshow()")
plt.show()

#! Kwantyzacja
# Zadanie 2
print(obraz.ndim)

# Zadanie 3
image = Image.open("C:/Users/smh2k/Desktop/PIAD/Lab4/robal.png")
print(image.getbands)

# Zadanie 4
# oryginal
plt.subplot(2,2,1)
plt.title('Oryginal')
plt.imshow(obraz)
# wyznaczenie jasnosci piksela
o1 = plt.subplot(2,2,2)
plt.title('Metoda wyznaczania jasnosci piksela')
szarosc1 = (np.max(obraz,axis=2)+np.min(obraz,axis=2))/2
o1.imshow(szarosc1,cmap='gray')
# usrednienie wartosci piksela
o2 = plt.subplot(2,2,3)
plt.title('Metoda usrednienia wartosci piksela')
szarosc2 = np.mean(obraz,axis=2)
o2.imshow(szarosc2,cmap='gray')
# wyznaczenie luminacji piksela
o3 = plt.subplot(2,2,4)
plt.title('Wyznaczenie luminacji piksela')
szarosc3 = 0.21*obraz[:,:,0]+0.72*obraz[:,:,1]+0.07*obraz[:,:,2]
o3.imshow(szarosc3,cmap='gray')
plt.show()
 
# Zadanie 5
dane1, bins1= np.histogram(szarosc1, bins=250)
dane2, bins2= np.histogram(szarosc2, bins=250)
dane3, bins3= np.histogram(szarosc3, bins=250)
plt.hist(bins1[:-1], bins1, weights=dane1)
plt.title('Histogram: Wyznaczenie jasności piksela')
plt.show()
plt.hist(bins2[:-1], bins2, weights=dane2)
plt.title("Histogram: Urdenienie wartości piksela")
plt.show()
plt.hist(bins3[:-1], bins3, weights=dane3)
plt.title('Histogram: Wyznaczenie luminacji piksela')
plt.title
plt.show()

# Zadanie 6
x, y = np.histogram(szarosc3,bins=16)
plt.hist(y[:-1], y, weights=x)
plt.axvline(sum(y)/len(y), color='red', linestyle='--')
plt.title("Histogram po redukcji liczby kolorow")
plt.show()

#! Binaryzacja
# Zadanie 1 i 2
obraz = plt.imread("C:/Users/smh2k/Desktop/PIAD/Lab4/robal.png")
szarosc = (np.max(obraz,axis=2)+np.min(obraz,axis=2))/2
dane, bins = np.histogram(szarosc, bins=250)
plt.hist(bins[:-1], bins, weights=dane)
plt.show()

# Zadanie 3
val = filters.threshold_otsu(szarosc)
hist, bins_center = exposure.histogram(szarosc)

# Zadanie 4 i 5 
plt.subplot(1,2,1)
plt.imshow(szarosc < val, cmap='gray', interpolation='nearest')
plt.subplot(1,2,2)
plt.imshow(szarosc > val, cmap='gray', interpolation='nearest')
plt.show()
# Histogram
plt.plot(bins_center, hist, lw=2)
plt.axvline(val, color='k', ls='--')
plt.show()