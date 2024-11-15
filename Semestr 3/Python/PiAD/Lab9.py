import IPython.display
import sounddevice as sd
import soundfile as sf
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp
from scipy.stats import kurtosis
import scipy.fftpack
from IPython.display import Audio
import IPython
import librosa


#Czesc pierwsza - sygnal audio
s, fs = sf.read("Lab9/ZuT2.wav", dtype='float32')
file ="Lab9/ZuT2.wav"
IPython.display.Audio(file)
# print(s[:,0])
time = np.arange(s.shape[0])/fs*1000
plt.plot(time,s[:,0])
plt.show()

#Zadanie 4
#Zakres dynamiki sygnalu
dynamika = np.max(np.abs(s[:,0])) - np.min(np.abs(s[:,0]))
#Sprawdzanie czy sygnal jest przesterowany
if np.any(np.abs(s[:,0])) > 1:
    print("Sygnal jest przesterowany")
else:
    print("Sygnal nie jest przesterowany")
#Amplituda szumu na poczatku i koncu nagrania
poczatek = np.std(s[:fs])
koniec = np.std(s[-fs:])
# Sprwadzanie losowosci szumu
if (np.abs(kurtosis(poczatek))) < 3:
    print("Szum na poczatku ma charatker losowy")
else:
    print("Szum na poczatku nie ma charakteru losowego")

if (np.abs(kurtosis(koniec))) < 3:
    print("Szum na koncu ma charatker losowy")
else:
    print("Szum na koncu nie ma charakteru losowego")


#Czesc 2 - zastosowanie okien kroczacych
# Zadanie 1
sygnal = s[:,0]
def E(frame):
    return np.sum(frame ** 2)

def Z(frame):
    return np.sum(frame[:-1] * frame[1:] < 0)

def okna_kroczace(ramka_ms, pokrywanie = False):
    ramka_probki = int(fs * ramka_ms / 1000)
    ramki = int(len(s) / ramka_probki)
    energia = []
    przejscia0 = []
    for i in range(ramki):
        if pokrywanie == False:
            ramka = s[i * ramka_probki : (i + 1) * ramka_probki]
        else:
            ramka = s[i * (ramka_probki//2) : (i + 1) * ramka_probki]
        # print(ramka)
        energia.append(E(ramka))
        przejscia0.append(Z(ramka))
    #Normalizacja 
    energia = np.array(energia)/np.max(energia)
    przejscia0 = np.array(przejscia0)/np.max(przejscia0)

    # Zadanie 2
    # Przeliczenie czasu na milisekundy dla ramki
    ramka_czas = np.arange(ramki) * ramka_ms
    # Wykresy
    plt.plot(time, sygnal, c='green', label="Sygnal")
    plt.plot(ramka_czas, energia, c='blue', label="Funkcja energii")
    plt.plot(ramka_czas, przejscia0, c="red", label="Przejscia przez 0")
    plt.title("Rozmiar okna: " +  str(ramka_ms) + " ms")
    plt.legend()
    plt.show()
#Podzial sygnalu
ramka_ms = 10
okna_kroczace(ramka_ms)

# Zadanie 3
# W przypadki maksimum funkcji energii oraz minimum funkcji przejść wskazują na 'najgłośniejszą' ramke sygnału 
# natomiast minimum funkcji energii oraz maksimum funkcji przejść wskazują na 'najcichszą' ramke. 
# W segmentach dźwiecznych zwiększają się wartości energi oraz maleje liczba przejść przez 0
# natomiast w segmentach bezdźwięcznych występuje sytuacja odwrotna, energia przybiera wartości niższe bądź 0
# a liczba przejść przez 0 wzrasta

#Na tej podstawie można rozdzielić sygnał na
#Samogłoski -> duże wartosci E, małe wartości Z
#Spółgłoski dźwięczne -> E i Z mają podobne wartości
#Spółgłoski bezdźwięczne -> małe wartości E, duże wartości Z
#Spółgłoski nosowe -> Średnie wartości E, małe wartości Z

# Zadanie 4
okna_kroczace(5)
okna_kroczace(20)
okna_kroczace(50)

# Zadanie 5
okna_kroczace(20,True)
# Nakładanie ramek zwiększa gładkość wyników i pozwala zwiększyć dokładność detekcji


# 3 - Analiza częstotliwościowa
# Zadanie 1
fragment = sygnal[int(420*fs/1000):int(420*fs/1000)+2048]
sd.play(fragment, fs)
sd.wait()

# Zadanie 2
maskowanie = np.hamming(2048)
okno_zamaskowane = fragment * maskowanie

# Zadanie 3 i 4
yf = scipy.fftpack.fft(okno_zamaskowane)
widmo = np.log(np.abs(yf))
fk = []
for i in range(len(widmo)):
    fk.append(i*fs/len(widmo))
plt.plot(fk,widmo)
plt.xlim(0,10000)
plt.xlabel('Czestotliwosc [Hz]')
plt.ylabel('Amplituda')
plt.show()

# 4 - rozpoznawanie samogłosek ustnych
# Zadanie 1,2
okno = sygnal[int(420*fs/1000):int(420*fs/1000)+2048]
p = 20
a = librosa.lpc(okno, order=p)

# Zadanie 3
# Liniowe Kodowanie Predykcyjne to technika analizy sygnałów, szczególnie używana w przetwarzaniu mowy. Polega na modelowaniu sygnału mowy 
# jako liniowej kombinacji poprzednich próbek sygnału. Jest to technika używana do kompresji, analizy, syntezy mowy oraz filtracji adaptacyjnej i redukcji szumów

# Zadanie 4
a = np.pad(a, (0,2048-len(a)), 'constant')

# Zadanie 5
widmoLPC = np.log(np.abs(scipy.fftpack.fft(a)))
widmoLPC = widmoLPC*(-1)
fk2 = []
for i in range(len(a)):
    fk2.append(i*fs/len(a))
plt.plot(fk2,widmo)
plt.plot(fk2,widmoLPC+48)
plt.xlim(0,8000)
plt.xlabel('Czestotliwosc [Hz]')
plt.ylabel('Amplituda')
plt.show()