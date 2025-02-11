
#include<iostream>
#include<time.h>
#include<stdio.h>
#include<string>
#include<random>
#include<cmath>
using namespace std;
string klucz;
char litery[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
const int mnoznik = 2;

template <typename T>
struct element {
	string klucz;
	T wartosc;
	element<T>* next;
	element() {
		klucz = "";
		wartosc = nullptr;
		next = nullptr;
	}
	element(string klucz, T wartosc) {
		this->klucz = klucz;
		this->wartosc = wartosc;
		this->next = nullptr;
	}
	string printElement()
};

template<typename T>
string element<T>::printElement() {
	return "Klucz: " + this->klucz + "->Wartosc: " + to_string(this->wartosc);
}

template <typename T>
class Lista {
public:
	element<T>* head;
	Lista() {
		head = nullptr;
	}

	element<T>* szukaj(string klucz);
	bool dodaj(string klucz, T wartosc);
	bool usun(string klucz);
};

template <typename T>
element<T>* Lista<T>::szukaj(string klucz) {
	element<T>* temp = head;
	if (temp == nullptr) return nullptr;
	else {
		while (temp != nullptr) {
			if (temp->klucz == klucz) {
				return temp;
			}
			temp = temp->next;
		}
	}
	return nullptr;
}

template <typename T>
bool Lista<T>::dodaj(string klucz, T wartosc) {
	element<T>* nowy = new element<T>(klucz, wartosc);
	if (szukaj(klucz) == nullptr) {
		if (head == nullptr) {
			head = nowy;
		}
		else {
			element<T>* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = nowy;
		}
		return true;
	}
	else {
		element<T>* temp = szukaj(klucz);
		temp->wartosc = wartosc;
		return false;
	}
}

template <typename T>
bool Lista<T>::usun(string klucz) {
	if (szukaj(klucz) == NULL) return false;
	else {
		element<T>* temp = szukaj(klucz);
		if (temp == head) {
			head = temp->next;
		}
		else {
			element<T>* par = head;
			while (par->next != temp) {
				par = par->next;
			}
			par->next = temp->next;
		}
		return true;
	}
	return false;
}
template <typename T>
class HashTable {
public:
	int pojemnosc;
	double zapelnienie;
	int rozmiar;
	Lista<T>* table;
	void addElem(string klucz, T wartosc);
	void findElem(string klucz);
	void deleteElem(string klucz);
	void clear();
	void printout();
	int hashFunction(string klucz);
	void rehash();
	HashTable() {
		rozmiar = 0;
		zapelnienie = 0;
		pojemnosc = 4;
		table = new Lista<T>[pojemnosc];
	}
};

template <typename T>
void HashTable<T>::addElem(string klucz, T wartosc) {
	long int hashValue = hashFunction(klucz);
	bool success = this->table[hashValue].dodaj(klucz, wartosc);
	if (success == true) {
		rozmiar++;
	}
	if (((double)rozmiar/(double)pojemnosc) > 0.75) {
		rehash();
	}
}

template <typename T>
void HashTable<T>::findElem(string klucz) {
	long long int hashValue = hashFunction(klucz);
	element<T>* temp = table[hashValue].szukaj(klucz);
	if (temp != nullptr) {
		cout << temp->printElement();
	}
	else {
		cout << "Nie ma elementu o danym kluczu" << endl;
	}
}

template <typename T>
void HashTable<T>::deleteElem(string klucz) {
	long long int hashValue = hashFunction(klucz);
	bool success = this->table[hashValue].usun(klucz);
	if (success == true) {
		rozmiar--;
	}
}

template <typename T>
void HashTable<T>::clear() {
	delete[] table;
	pojemnosc = 4;
	table = new Lista<T>[pojemnosc];
	zapelnienie = 0;
	rozmiar = 0;
}

template <typename T>
void HashTable<T>::printout() {
	cout << "-----------Tablica Mieszajaca-----------" << endl;
	double srdlg = 0;
	int nn = 0;
	int licznik = 0;
	for (int i = 0; i < pojemnosc; i++) {
		licznik = 0;
		if (table[i].head != nullptr) {
			element<T>* temp = table[i].head;
			cout << "Klucz: " << temp->klucz << "->Wartosc: " << temp->wartosc;
			nn++;
			licznik++;
			temp = temp->next;
			while (temp != nullptr) {
				cout << ", " << "Klucz: " << temp->klucz << "->Wartosc: " << temp->wartosc;
				temp = temp->next;
				licznik++;
			}
			cout << ";" << endl;
			srdlg += licznik;
		}
	}
	cout << "Obecny rozmiar: " << rozmiar << endl;
	cout << "Maksymalna pojemnosc: " <<pojemnosc << endl;
	cout << "Poziom zapelnienia: " << (double)zapelnienie << endl;
	cout << "Srednia dlugosc listy: " << (double)(srdlg / (double)nn) << endl;
}

template <typename T>
int HashTable<T>::hashFunction(string klucz) {
	unsigned long long int hashValue = 0;
	for (int i = 0; i < klucz.length(); i++) {
		hashValue += (klucz[i] * 31 ^ (klucz.length() - (i + 1)));
	}
	hashValue = hashValue % pojemnosc;
	return hashValue;
}

template <typename T>
void HashTable<T>::rehash() {
	Lista<T>* temp = new Lista<T>;
	for (int i = 0; i < pojemnosc; i++) {
		element<T>* tempEl = table[i].head;
		while (tempEl != nullptr) {
			temp->dodaj(tempEl->klucz, tempEl->wartosc);
			tempEl = tempEl->next;
		}
		delete[] tempEl;
	}
	pojemnosc = pojemnosc * mnoznik;
	delete[] table;
	table = new Lista<T>[pojemnosc];
	element<T>* tempEl = temp->head;
	while (tempEl != nullptr) {
		long long int hashValue = hashFunction(tempEl->klucz);
		table[hashValue].dodaj(tempEl->klucz, tempEl->wartosc);
		tempEl = tempEl->next;
	}
}

string keyGenerator() {
	klucz = "";
	for (int i = 0; i < 6; i++) {
		klucz += (litery[rand() % 26]);
	}
	//cout << klucz << endl
	return klucz;
}

int main() {
	HashTable<int> HT;
	for (int i = 1; i < 101; i++) {
		HT.addElem(keyGenerator(), i*(i-1));
	}
	for (;;) {
		HT.zapelnienie = (double)HT.rozmiar / (double)HT.pojemnosc;
		cout << "Obecny rozmiar: " << HT.rozmiar << endl;
		cout << "Maksymalna pojemnosc: " << HT.pojemnosc << endl;
		cout << "Poziom zapelnienia: " << (double)HT.zapelnienie << endl;
		int wybor;
		cout << "1.Dodaj element" << endl;
		cout << "2.Znajdz element" << endl;
		cout << "3.Usun element" << endl;
		cout << "4.Czysczenie tablicy" << endl;
		cout << "5.Wypisz elementy" << endl;
		cout << "6.Wyjdz" << endl;
		cout << "Wybor: ";
		cin >> wybor;
		if (wybor == 1) {
			string klucz;
			int wartosc;
			cout << "Podaj klucz: ";
			cin >> klucz;
			cout << "Podaj wartosc: ";
			cin >> wartosc;
			clock_t t1 = clock();
			HT.addElem(klucz, wartosc);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Czas wykonania: " << time << endl;
		}
		else if (wybor == 2) {
			string klucz;
			cout << "Podaj klucz ktory chcesz znalezc: ";
			cin >> klucz;
			clock_t t1 = clock();
			HT.findElem(klucz);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Czas wykonania: " << time << endl;
		}
		else if (wybor == 3) {
			string klucz;
			cout << "Podaj klucz do usuniecia: " << endl;
			cin >> klucz;
			clock_t t1 = clock();
			HT.deleteElem(klucz);
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Czas wykonania: " << time << endl;
		}
		else if (wybor == 4) {
			clock_t t1 = clock();
			HT.clear();
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Czas wykonania: " << time << endl;
		}
		else if (wybor == 5) {
			clock_t t1 = clock();
			HT.printout();
			clock_t t2 = clock();
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			cout << "Czas wykonania: " << time << endl;
		}
		else {
			break;
		}
		system("pause");
		system("cls");
	}

	return 0;
}