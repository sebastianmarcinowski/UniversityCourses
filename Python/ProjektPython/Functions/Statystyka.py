import numpy as np
import scipy.stats as sp
from PyQt5.QtWidgets import QApplication,QLabel ,QWidget, QVBoxLayout,QGridLayout, QPushButton,QLineEdit, QDialog
import re
class Statystyka(QDialog):
    def __init__(self):
        super().__init__()
        self.layout = QVBoxLayout()
        self.setWindowTitle('Statystyka')
        self.setFixedSize(400,400)
        self.wektor = QLineEdit(self)
        self.button = QPushButton('Oblicz')
        self.button.clicked.connect(self.stat)
        self.wynik1 = QLabel('Średnia: ')
        self.wynik2 = QLabel('Suma: ')
        self.wynik3 = QLabel('Wariancja: ')
        self.wynik4 = QLabel('Współczynnik wariancji: ')
        self.wynik5 = QLabel('Odchylenie standardowe: ')
        self.layout.addWidget(self.wektor)
        self.layout.addWidget(self.wynik1)
        self.layout.addWidget(self.wynik2)
        self.layout.addWidget(self.wynik3)
        self.layout.addWidget(self.wynik4)
        self.layout.addWidget(self.wynik5)
        self.layout.addWidget(self.button)
        self.setStyleSheet("""QPushButton,QLineEdit,QLabel {font-size:20px}
                           QPushButton {background-color: rgb(90,90,90); font-size:20px; color:white}
                           QPushButton:hover {background-color: rgb(150,150,150); color:black}""")
        self.setLayout(self.layout)
    
    def stat(self):
        temp = re.findall(r'\d+',self.wektor.text())
        tab2 = [int(nums) for nums in temp]
        try:
            self.wynik1.setText('Średnia: ' + str(round(np.mean(tab2),2)))
            self.wynik2.setText('Suma: ' + str(round(np.sum(tab2),2)))
            self.wynik3.setText('Wariancja: ' + str(round(np.var(tab2),2)))
            self.wynik4.setText('Współczynnik wariancji: ' + str(round(sp.variation(tab2),2)))
            self.wynik5.setText('Odchylenie standardowe: ' + str(round(np.std(tab2),2)))
        except Exception as e:
            print("Błąd w podaniu wektora")