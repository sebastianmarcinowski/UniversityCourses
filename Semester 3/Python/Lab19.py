import PyQt5.QtWidgets as pq

# Zadanie 1
# def napis():
#     etykieta.setText("Pierwszy program gotowy")
# app = pq.QApplication([])
# okno = pq.QWidget()
# etykieta = pq.QLabel()
# guzik = pq.QPushButton("Guzik")
# guzik.clicked.connect(napis)
# uklad =  pq.QVBoxLayout()
# uklad.addWidget(etykieta)
# uklad.addWidget(guzik)

# okno.setLayout(uklad)
# guzik.show()
# okno.show()
# app.exec_()


# Zadanie 3
class Dialog(pq.QDialog):
    def __init__(self):
        super().__init__()
        self.layout = pq.QVBoxLayout()
        self.textbox1 = pq.QLineEdit("1")
        self.textbox2 = pq.QLineEdit("2")
        self.button1 = pq.QPushButton('Wynik')
        self.button1.clicked.connect(self.dodaj)
        self.button2 = pq.QPushButton('Akceptuj')
        self.button2.clicked.connect(self.accept)
        self.button3 = pq.QPushButton('Odrzuc')
        self.button3.clicked.connect(self.close)
        self.layout.addWidget(self.textbox1)
        self.layout.addWidget(self.textbox2)
        self.layout.addWidget(self.button1)
        self.layout.addWidget(self.button2)
        self.layout.addWidget(self.button3)
        self.setLayout(self.layout)
    def dodaj(self):
        return str(int(self.textbox1.text())+int(self.textbox2.text()))
class MainWindow(pq.QWidget):
    def __init__(self,app):
        super().__init__()
        self.setFixedSize(200,200)
        self.layout = pq.QVBoxLayout()
        self.textbox = pq.QLabel()
        self.button = pq.QPushButton('Show Dialog')
        self.button.clicked.connect(self.on_show_dialog)
        self.layout.addWidget(self.textbox)
        self.layout.addWidget(self.button)
        self.setLayout(self.layout)
        self.show()
    def on_show_dialog(self):
        dial = Dialog() 
        if(dial.exec_() == pq.QDialog.Accepted):
            print("Jest G")
        elif(dial.exec_() == pq.QDialog.close):
            print("Koniec")

app  = pq.QApplication([])
nowe = MainWindow(app)
app.exec_()