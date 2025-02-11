
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

struct Wezel {
	double x; //wspolrzedna x wezla
	double y; //wspolrzedna y wezla
	int index; //indeks wezla
	Wezel(double x, double y, int index) : x(x), y(y), index(index) {}
};

struct Krawedz {
	int poczatek;
	int koniec;
	double koszt;
	Krawedz(int poczatek, int koniec, double koszt) : poczatek(poczatek), koniec(koniec), koszt(koszt) {}
};

template <typename T>
class DynamicTable {
public:
	int pojemnosc;
	int rozmiar;
	T data;
	T* test = NULL;
	T& operator[](size_t index) {
		return test[index];
	}
	void dodaj(T data);
	void czysc();
	void sort();
	void BucketSort(int n, float m);
	//void wypisz();
	DynamicTable(int r = 0, int p = 1) {
		rozmiar = r;
		pojemnosc = p;
		test = new T[pojemnosc];
	}
};
template <typename T>
void DynamicTable<T>::dodaj(T data) {
	if (pojemnosc <= rozmiar) {
		pojemnosc = pojemnosc * 4;
		T* temp = new T[pojemnosc];
		for (int i = 0; i < rozmiar; i++) {
			temp[i] = test[i];
		}
		delete[] test;
		test = temp;
	}
	test[rozmiar] = data;
	rozmiar++;
}
template <typename T>
void DynamicTable<T>::czysc() {
	test[1];
	rozmiar = 0;
	pojemnosc = 1;
}
template <typename T>
void DynamicTable<T>::sort() {
	T temp;
	for (int i = 0; i < rozmiar; i++) {
		bool flaga = false;
		for (int j = 0; j < rozmiar - i -1; j++) {
			if (test[j], test[j + 1]) {
				temp = test[j + 1];
				test[j + 1] = test[j];
				test[j] = temp;
				flaga = true;
			}
		}
		if (flaga == false) {
			break;
		}
	}
}

template <typename T>
void DynamicTable<T>::BucketSort(int n, float m) {
	DynamicTable<T>* wiadra = new DynamicTable<T>[n];

	for (int i = 0; i < n; i++) {
		int id = test[i]->koszt / (m / (float)n);
		wiadra[id].dodaj(test[i]);
	}
	for (int i = 0; i < n; i++) {
		if (wiadra[i].rozmiar > 0) {
			wiadra[i].sort();
		}
	}
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < wiadra[i].rozmiar; j++) {
			test[k] = wiadra[i][j];
			k++;
		}
	}
	delete[] wiadra;
}
class Graf {
public:
	DynamicTable<Wezel*>* wezly = new DynamicTable<Wezel*>();
	DynamicTable<Krawedz*>* krawedzie = new DynamicTable<Krawedz*>();

	void dodajWezel(double x, double y, int index) {
		Wezel* wezel = new Wezel(x, y, index);
		wezly->dodaj(wezel);
	}

	void dodajKrawedz(int poczatek, int koniec, double koszt) {
		Krawedz* krawedz = new Krawedz(poczatek, koniec, koszt);
		krawedzie->dodaj(krawedz);
	}
	void pokaz() {
		for (int i = 0; i < krawedzie->rozmiar; i++) {
			Krawedz* edge = krawedzie->test[i];
			cout << "Poczatek: " << edge->poczatek << ", Koniec: " << edge->koniec << ", Koszt: " << edge->koszt << endl;
		}
	}
};

class Union_Find {
public:
	DynamicTable<int>* id_rodzic = new DynamicTable<int>();
	DynamicTable<int>* rangi = new DynamicTable<int>();
	Union_Find(int n) {
		for (int i = 0; i < n; i++) {
			id_rodzic->dodaj(i);
			rangi->dodaj(0);
		}
	}

	//Funkcje do laczenia zbiorow
	void ClassicUnion(int id1, int id2) {
		int id1F = ClassicFind(id1);
		int id2F = ClassicFind(id2);
		id_rodzic->test[id1F] = id2F;
	}
	void Union_By_Rank(int id1, int id2) {
		int id1F = PathCompression(id1);
		int id2F = PathCompression(id2);
		int id1Ranga = rangi->test[id1];
		int id2Ranga = rangi->test[id2];

		if (id1F == id2F) {
			return;
		}

		if (id1Ranga > id2Ranga) {
			id_rodzic->test[id2F] = id1F;
		}
		else if (id1Ranga < id2Ranga) {
			id_rodzic->test[id1F] = id2F;
		}
		else {
			id_rodzic->test[id1F] = id2F;
			rangi->test[id2F]++;
		}
	}

	//Funkcje znajdowania reprezentanta zbioru
	int ClassicFind(int indeks) {
		if (id_rodzic->test[indeks] == indeks) {
			return indeks;
		}
		else {
			return ClassicFind(id_rodzic->test[indeks]);
		}
	}
	int PathCompression(int indeks) {
		if (id_rodzic->test[indeks] == indeks) {
			return indeks;
		}
		int path = PathCompression(id_rodzic->test[indeks]);
		id_rodzic->test[indeks] = path;
		return path;
	}
};



void odczytPliku(Graf* graf, string nazwa) {
	fstream plik;
	plik.open(nazwa, ios::in);
	if (plik.good() == false) {
		cout << "Blad przy odczycie z pliku" << endl;
		return;
	}
	int n;
	plik >> n;
	//cout << n << endl;
	for (int i = 0; i < n; i++) {
		double x =0.0;
		double y = 0.0;
		plik >> x >> y;
		graf->dodajWezel(x, y, i);
		//cout << x << " " << y << endl;
	}
	int e;
	plik >> e;
	cout << e << endl;
	for (int i = 0; i < e; i++) {
		int id1;
		int id2;
		double waga;
		plik >> id1 >> id2 >> waga;
		graf->dodajKrawedz(id1, id2, waga);
		//cout << id1 << " " << id2 << " " << waga << endl;
	}
	plik.close();
}

void Kruskal(Graf* graf, bool war1){
	int licznik = 0;
	int k = graf->krawedzie->rozmiar; //liczba krawedzi grafu
	int w = graf->wezly->rozmiar; //liczba wezlow grafu
	Union_Find* uf = new Union_Find(w);
	//Sortowanie krawedzi
	clock_t b1 = clock();
	graf->krawedzie->BucketSort(k, 1.0);
	//cout << "dsa" << endl;
	//graf->pokaz();
	clock_t b2 = clock();
	//Petla glowna algorytmu Kruskala
	DynamicTable<Krawedz*>* MST = new DynamicTable<Krawedz*>();
	clock_t t1 = clock();
	if (war1 == false) {
		for (int i = 0; i < k; i++) {
			int pk = uf->ClassicFind(graf->krawedzie->test[i]->poczatek);
			int kk = uf->ClassicFind(graf->krawedzie->test[i]->koniec);
			if (pk != kk) {
				MST->dodaj(graf->krawedzie->test[i]);
				uf->Union_By_Rank(pk, kk);
			}
			licznik += 2;
		}
	}
	else if (war1 == true) {
		for (int i = 0; i < k; i++) {
			int pk = uf->PathCompression(graf->krawedzie->test[i]->poczatek);
			int kk = uf->PathCompression(graf->krawedzie->test[i]->koniec);
			if (pk != kk) {
				MST->dodaj(graf->krawedzie->test[i]);
				uf->Union_By_Rank(pk, kk);
			}
			licznik += 2;
		}
	}
	clock_t t2 = clock();
	double suma = 0.0;
	for (int i = 0; i < MST->rozmiar; i++) {
		suma += MST->test[i]->koszt;
	}
	//Wyswietlenie MST
	/*for (int i = 0; i < MST->rozmiar; i++) {
		cout << "Poczatek: " << MST->test[i]->poczatek << " Koniec: " << MST->test[i]->koniec << " Waga: " << MST->test[i]->koszt << endl;
	}*/
	double timebucket = (b2 - b1) / (double)CLOCKS_PER_SEC;
	double timepetla = (t2 - t1) / (double)CLOCKS_PER_SEC;
	cout << "Liczba krawedzi: " << MST->rozmiar << " Suma wag: " << suma << endl;
	cout << "Czas sortowania: " << timebucket << endl;
	cout << "Czas petli glownej: " << timepetla << endl;
	cout << "Liczba operacji find: " << licznik << endl;
	delete[] MST;
	delete uf;
}

int main() {
	Graf* graf = new Graf;
	odczytPliku(graf, "g3.txt");
	//graf->pokaz();


	bool w1 = false; //Opcja 1 -> PathCompression | false = Classic Find
	bool w2 = true; //Opcja 2 -> Union by Rank | false = Classic Union 
	Kruskal(graf, w1);
	return 0;
}