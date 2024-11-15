import math
from PyQt5.QtWidgets import QHBoxLayout,QSizePolicy,QApplication,QLabel ,QWidget, QVBoxLayout,QGridLayout, QPushButton,QLineEdit, QDialog
from PyQt5.QtCore import Qt
import scipy as sc
import numpy as np
import matplotlib.pyplot as plt
from Functions import Statystyka as st
from Functions import Trygonometria as tg
from BasicOperations import Operacje as bo

# Reset zawartosci pliku
plik = open('HistoriaObliczen.txt','w+')
plik.close()

# Klasa tworzaca glowne okno kalkulatora
class Kalkulator(QWidget):
    def __init__(self):
        self.trygvalue = True #zmiennie uzywana przy zamianie wyniku funkcji trygonometrycznych z radianow na stopnie i vice versa
        self.ostatnie_dzialanie = '' #flaga uzywana przy dzialaniach x^y od mod
        super().__init__()
        self.setWindowTitle("Kalkulator naukowy")
        self.setFixedSize(800,400)
        self.layout = QVBoxLayout()
        self.historia = QLabel()
        self.historia.setObjectName('historia')
        self.historia.setAlignment(Qt.AlignTop)
        self.historia.setFixedSize(300,300)
        self.pamiec = QLabel('Pamięć')
        self.wynik = QLineEdit(self)
        self.wynik.setFixedWidth(480)
        self.wynik.setPlaceholderText("Wynik")
        self.layout.addWidget(self.pamiec)
        self.layout.addWidget(self.wynik)
        self.layout.setSpacing(0)
        self.setLayout(self.layout)
        self.buttons()

    # Funkcja tworzaca oraz ukladajaca przyciski
    def buttons(self):
        self.buttons = ['rad','pi','e','CE','<-',
                   'x^2','1/x','stat','exp','mod',
                   '√x','(',')','n!','/',
                   'x^y','7','8','9','*',
                   '10^x','4','5','6','-',
                   'log','1','2','3','+',
                   'ln','tryg','0','.','=',]
        self.grid = QGridLayout()
        row,col =0,0
        for buttonText in self.buttons:
            self.button = QPushButton(buttonText, self)
            if buttonText in ['1','2','3','4','5','6','7','8','9','0',]:
                self.button.setObjectName("numery")
            elif buttonText == '=':
                self.button.setObjectName("rownasie")
            else:
                self.button.setObjectName("guzik")
            self.button.clicked.connect(self.button_click)
            self.grid.addWidget(self.button, row, col)
            col += 1
            if col > 4:
                col = 0
                row += 1
        self.grid.addWidget(self.historia,0,6)
        self.layout.addLayout(self.grid)
        self.setStyleSheet("""#guzik {background-color: rgb(90,90,90); color:white}
                           #rownasie {background-color: rgb(90,90,90); color:white}
                           #numery {background-color: rgb(150,150,150)}
                           QPushButton {width:35px; height:35px; font-size:20px}
                           #numery:hover {background-color: rgb(90,90,90); color:white}
                           #guzik:hover {background-color: rgb(150,150,150); color:black}
                           #rownasie:hover {background-color: rgb(150,150,150); color:black}
                           QLineEdit {height: 50px; font-size: 35px}
                           QLabel {font-size: 20px; color: rgb(150,150,150)}
                           #historia {border: 3px solid rgb(90,90,90); color:rgb(90,90,90)}""")

    #Funkcja do obsługi przycisków
    def button_click(self):
        plik = open('HistoriaObliczen.txt','a')
        uzytkowe = ['stat','tryg','1/x','x^2','√x','x^y','10^x','log','ln','mod','n!','exp','pi','e']
        button = self.sender()
        if self.wynik.text() in uzytkowe:
            dzialanie = ''
        else:
            dzialanie = self.wynik.text()
        if button.text() == '=':
            if(self.ostatnie_dzialanie == 'x^y'):
                x = float(self.pamiec.text()[0:-1])
                self.wynik.setText(str(bo.potegaxy(x,float(dzialanie))))
                self.pamiec.setText('')
                self.ostatnie_dzialanie = ''
                return
            elif(self.ostatnie_dzialanie == 'mod'):
                x = int(self.pamiec.text()[0:-3])
                self.wynik.setText(str(bo.modulo(x,int(dzialanie))))
                self.pamiec.setText('')
                self.ostatnie_dzialanie = ''
                return
                return
            try:
                result = eval(dzialanie)
                self.wynik.setText(str(result))
            except Exception as e:
                self.wynik.setText("Błąd")
            plik.write(self.wynik.text()+"\n")
            plik.close()
            self.historiaObliczen()
        elif button.text() == 'stat': #wywolanie okna do statystyki
            self.statystyka()
        elif button.text() == 'tryg': #wywolanie okna z funkcjami trygonometrycznymi
            self.trygonometria()
        elif button.text() == 'pi':
            self.wynik.setText(dzialanie + str(round(math.pi,4)))
            plik.write(self.wynik.text()+"\n")
            plik.close()
            self.historiaObliczen()
        elif button.text() == 'e':
            self.wynik.setText(dzialanie + str(round(math.exp(1),4)))
            plik.write(self.wynik.text()+"\n")
            plik.close()
            self.historiaObliczen()
        elif button.text() == 'n!':
            try:
                wynik = bo.silnia(int(dzialanie))
                self.wynik.setText(str(wynik))
            except Exception:
                self.wynik.setText('Błąd')
            plik.write(self.wynik.text()+"\n")
            plik.close()
            self.historiaObliczen()
        elif button.text() == '√x':
            try:
                wynik = bo.pierwiastek(float(dzialanie))
                self.wynik.setText(str(wynik))
            except Exception:
                self.wynik.setText('Błąd')
            plik.write(self.wynik.text()+"\n")
            plik.close()
            self.historiaObliczen()
        elif button.text() == '1/x':
            try:
                wynik = bo.ulamek(float(dzialanie))
                self.wynik.setText(str(wynik))
            except Exception:
                self.wynik.setText('Błąd')
            plik.write(self.wynik.text()+"\n")
            plik.close()
            self.historiaObliczen()
        elif button.text() == 'x^2':
            try:
                wynik = bo.potega2(float(dzialanie))
                self.wynik.setText(str(wynik))
            except Exception:
                self.wynik.setText('Błąd')
            plik.write(self.wynik.text()+"\n")
            plik.close()
            self.historiaObliczen()
        elif button.text() == 'log':
            try:
                wynik = bo.loga10(float(dzialanie))
                self.wynik.setText(str(wynik))
            except Exception:
                self.wynik.setText('Błąd')
            plik.write(self.wynik.text()+"\n")
            plik.close()
            self.historiaObliczen()
        elif button.text() == 'ln':
            try:
                wynik = bo.ln(float(dzialanie))
                self.wynik.setText(str(wynik))
            except Exception:
                self.wynik.setText('Błąd')
            plik.write(self.wynik.text()+"\n")
            plik.close()
            self.historiaObliczen()
        elif button.text() == '10^x':
            try:
                wynik = bo.potega10(float(dzialanie))
                self.wynik.setText(str(wynik))
            except Exception:
                self.wynik.setText('Błąd')
            plik.write(self.wynik.text()+"\n")
            plik.close()
            self.historiaObliczen()
        elif button.text() == 'x^y':
            self.pamiec.setText(dzialanie +'^')
            self.wynik.clear()
            self.ostatnie_dzialanie = 'x^y'
        elif button.text() == 'exp': 
            try:
                wynik = bo.exp(float(dzialanie))
                self.wynik.setText(str(wynik))
            except Exception:
                self.wynik.setText('Błąd')
            plik.write(self.wynik.text()+"\n")
            plik.close()
            self.historiaObliczen()
        elif button.text() == 'mod':
            self.pamiec.setText(dzialanie +'mod')
            self.wynik.clear()
            self.ostatnie_dzialanie = 'mod'
        elif button.text() == 'CE': #czyszczenie okna wyniku
            self.wynik.clear()
        elif button.text() == '<-': #usuwanie znakow z okna wyniku
            # Poprawa usuwania znakow, zeby zamiast pojedynczego elementu usuwać również cały funkcje np.mod
            tablica = ['x^2','1/x','exp','mod','√x','x^y','n!','10^x', 'log','ln', 'Błąd']
            if (dzialanie[-4::1] in tablica) and len(dzialanie)==4:
                usun = dzialanie[0:len(dzialanie)-4]
            elif (dzialanie[-3::1] in tablica) and len(dzialanie)==3:
                usun = dzialanie[0:len(dzialanie)-3]
            elif (dzialanie[-3::1] in tablica) and len(dzialanie)>3:
                usun = dzialanie[0:len(dzialanie)-3]
            elif (dzialanie[-2::1] in tablica) and len(dzialanie)==2:
                usun = dzialanie[0:len(dzialanie)-2]
            elif (dzialanie[-2::1] in tablica) and len(dzialanie)>2:
                usun = dzialanie[0:len(dzialanie)-2]
            else:
                usun = dzialanie[0:len(dzialanie)-1]
            self.wynik.setText(usun)
        elif button.text() == '|x|':
            pass
        #Ponizsze 2 elify sluza do zamiany wyswietlania wyniku funkcji trygonometrycznych z radianow na stopnie i odwrotnie
        elif button.text() == 'rad':
            button.setText('deg')
            self.trygvalue = False
        elif button.text() == 'deg':
            button.setText('rad')
            self.trygvalue = True
        elif button.objectName() == 'guzik':
            # Zapobieganie mozliwosci wystapienia wielu takich samych znakow/funkcji po sobie znakow dzialania po sobie
            if len(dzialanie) > 2 and dzialanie[-3::1] == button.text():
                self.wynik.setText(dzialanie)
            elif len(dzialanie) > 1 and dzialanie[-2::1] == button.text():
                self.wynik.setText(dzialanie)
            elif len(dzialanie) > 0 and dzialanie[-1] == button.text():
                self.wynik.setText(dzialanie)
            else:
                self.wynik.setText(dzialanie+button.text())
            
            # Podmiana znakow w sytuacji np. gdy po znaku + uzytkownik wcisnie znak *
            if len(dzialanie)==1 and dzialanie[-1]=='+' and button.text() in ['-','*','/']:
                self.wynik.setText(button.text())
            elif len(dzialanie) > 1 and dzialanie[-1]=='+' and button.text() in ['-','*','/']:
                dzialanie = dzialanie[0:-1] + button.text()
                self.wynik.setText(dzialanie)
            if len(dzialanie)==1 and dzialanie[-1]=='-' and button.text() in ['+','*','/']:
                self.wynik.setText(button.text())
            elif len(dzialanie) > 1 and dzialanie[-1]=='-' and button.text() in ['+','*','/']:
                self.wynik.setText(dzialanie[0:-1]+button.text())
            if len(dzialanie)==1 and dzialanie[-1]=='*' and button.text() in ['-','+','/']:
                self.wynik.setText(button.text())
            elif len(dzialanie) > 1 and dzialanie[-1]=='*' and button.text() in ['-','+','/']:
                self.wynik.setText(dzialanie[0:-1]+button.text())
            if len(dzialanie)==1 and dzialanie[-1]=='/' and button.text() in ['-','*','+']:
                self.wynik.setText(button.text())
            elif len(dzialanie) > 1 and dzialanie[-1]=='/' and button.text() in ['-','*','+']:
                self.wynik.setText(dzialanie[0:-1]+button.text())
        else:
            self.wynik.setText(dzialanie+button.text())

    # Funkcja do wywolywania okna odpowiedzialnego za funkcje statystyczne
    def statystyka(self):
        stat = st.Statystyka()
        if(stat.exec_() == QDialog.Accepted):
            pass

    # Funkcja do wywolywania okna odpowiedzialnego za funkcje trygonometryczne
    def trygonometria(self):
        tryg = tg.Trygonometria(self.trygvalue)
        if(tryg.exec_() == QDialog.Accepted):
            pass
    
    # Funkcja sluzaca do wypisywania z pliku wynikow dzialan na ekran
    def historiaObliczen(self):
        d = self.historia.text()
        plik = open('HistoriaObliczen.txt','r')
        temp = plik.readlines()
        for i in temp:
            self.historia.setText(str(i)+d)
        plik.close()

app = QApplication([])
main = Kalkulator()
main.show()
app.exec_()
plik.close()