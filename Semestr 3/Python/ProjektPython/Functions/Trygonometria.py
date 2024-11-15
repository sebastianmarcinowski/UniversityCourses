import scipy as sp
import numpy as np
from PyQt5.QtWidgets import QApplication,QLabel ,QWidget, QVBoxLayout,QGridLayout, QPushButton,QLineEdit, QDialog

class Trygonometria(QDialog):
    def __init__(self, trygvalue):
        super().__init__()
        self.trygvalue = trygvalue
        self.layout = QVBoxLayout()
        self.setFixedSize(400,300)
        self.setWindowTitle('Trygonometria')
        self.wynik = QLineEdit()
        self.wynik.setPlaceholderText("Wynik")
        self.layout.addWidget(self.wynik)
        self.text1 = QLabel('Funkcje trygonometryczne:')
        self.sin = QPushButton('Sinus')
        self.sin.clicked.connect(self.tsin)
        self.cos = QPushButton('Cosinus')
        self.cos.clicked.connect(self.tcos)
        self.tng = QPushButton('Tangens')
        self.tng.clicked.connect(self.ttan)
        self.ctg = QPushButton('Cotangens')
        self.ctg.clicked.connect(self.tctg)
        self.sec = QPushButton('Secans')
        self.sec.clicked.connect(self.tsec)
        self.csc = QPushButton('Cosecans')
        self.csc.clicked.connect(self.tcsc)
        self.text2 = QLabel('Funkcje hiperboliczne:')
        self.sinh = QPushButton('Sinus')
        self.sinh.clicked.connect(self.hsin)
        self.cosh = QPushButton('Cosinus')
        self.cosh.clicked.connect(self.hcos)
        self.tngh = QPushButton('Tangens')
        self.tngh.clicked.connect(self.htan)
        self.ctgh = QPushButton('Cotangens')
        self.ctgh.clicked.connect(self.hctg)
        self.sech = QPushButton('Secans')
        self.sech.clicked.connect(self.hsec)
        self.csch = QPushButton('Cosecans')
        self.csch.clicked.connect(self.hcsc)

        self.layout.addWidget(self.text1)
        self.grid = QGridLayout()
        self.grid.addWidget(self.sin,0,0)
        self.grid.addWidget(self.cos,0,1)
        self.grid.addWidget(self.tng,0,2)
        self.grid.addWidget(self.ctg,1,0)
        self.grid.addWidget(self.sec,1,1)
        self.grid.addWidget(self.csc,1,2)
        self.layout.addLayout(self.grid)

        self.layout.addWidget(self.text2)
        self.grid2 = QGridLayout()
        self.grid2.addWidget(self.sinh,0,0)
        self.grid2.addWidget(self.cosh,0,1)
        self.grid2.addWidget(self.tngh,0,2)
        self.grid2.addWidget(self.ctgh,1,0)
        self.grid2.addWidget(self.sech,1,1)
        self.grid2.addWidget(self.csch,1,2)
        self.layout.addLayout(self.grid2)
        self.layout.setSpacing(0)
        self.setStyleSheet("""QPushButton {background-color: rgb(90,90,90); font-size:20px; color:white}
                           QPushButton:hover {background-color: rgb(150,150,150); color:black}
                           QLabel {font-size: 25px}
                           QLineEdit {font-size: 25px}""")
        self.setLayout(self.layout)

    def tsin(self):
        try:
            wynik = np.sin(float(self.wynik.text()))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")
    def tcos(self):
        try:
            wynik = np.cos(float(self.wynik.text()))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")
    def ttan(self):
        try:
            wynik = np.tan(float(self.wynik.text()))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")
    def tctg(self):
        try:
            wynik = float(1/np.tan(float(self.wynik.text())))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")
    def tsec(self):
        try:
            wynik = float(1/np.sin(float(self.wynik.text())))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")
    def tcsc(self):
        try:
            wynik = float(1/np.cos(float(self.wynik.text())))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")

    def hsin(self):
        try:
            wynik = np.sinh(float(self.wynik.text()))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")
    def hcos(self):
        try:
            wynik = np.cosh(float(self.wynik.text()))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")
    def htan(self):
        try:
            wynik = np.tanh(float(self.wynik.text()))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")
    def hctg(self):
        try:
            wynik = float(1/np.tanh(float(self.wynik.text())))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")
    def hsec(self):
        try:
            wynik = float(1/np.sinh(float(self.wynik.text())))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")
    def hcsc(self):
        try:
            wynik = float(1/np.cosh(float(self.wynik.text())))
            if self.trygvalue == False: np.rad2deg(wynik) 
            self.wynik.setText(str(round(wynik,4)))
        except:
            self.wynik.setText("Błąd")