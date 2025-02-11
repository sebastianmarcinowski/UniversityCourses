
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <time.h> //pomiar czasowy wykonania operacji
#include <random>
//#include "ArrayFunc.hpp"
using namespace std;

const int array_multiplier = 2;

template <typename T>
struct tablica {
    int pojemnosc;
    int rozmiar;
    T data;
    T* test = NULL;
    void dodaj(T data); //a
    void wyszukaj(); //b
    void zmiana(); //c
    void czysc(); //d
    void wypisz(); //e
    void sort(); //f
    void dodajWiele(int ilosc);
    tablica() {
        rozmiar = 0;
        pojemnosc = 1;
        test = new T[pojemnosc];
    }
};
template <typename T>
void tablica<T>::dodaj(T data) {
    if (pojemnosc <= rozmiar) {
        pojemnosc = pojemnosc * array_multiplier;
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
void tablica<T>::wypisz() {
    int id = 1;
    cout << "Obecna maksymalna pojemnosc: " << pojemnosc << endl;
    cout << "Liczba elementow: " << rozmiar << endl;
    for (int i = 0; i < rozmiar; i++) {
        cout << id << ". " << test[i] << endl;
        id++;
    }
}
template <typename T>
void tablica<T>::wyszukaj() {
    int id;
    cout << "Podaj id elementu ktory chcesz wyszukac: " << endl;
    cin >> id;
    clock_t t1 = clock();
    if (id > rozmiar) cout << "Podany indeks wykracza poza zakres" << endl;
    else {
        for (int i = 0; i < rozmiar; i++) {
            if (i == id) cout << test[i] << endl;
        }
    }
    clock_t t2 = clock();
    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    cout << "Czas wykonania: " << time << endl;
}
template <typename T>
void tablica<T>::zmiana() {
    wypisz();
    int id;
    T wartosc;
    cout << "Podaj id elementu ktorego dane chcesz zmienic: ";
    cin >> id;
    clock_t t1 = clock();
    if (id > rozmiar) cout << "Nie ma elementu o takim id" << endl;
    else {
        cout << "Podaj nowa wartosc: ";
        cin >> wartosc;
        test[id - 1] = wartosc;
    }
    clock_t t2 = clock();
    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    cout << "Czas wykonania: " << time << endl;
}
template <typename T>
void tablica<T>::czysc() {
    test[1];
    rozmiar = 0;
    pojemnosc = 1;
}
template <typename T>
void tablica<T>::sort() {
    T temp;
    // clock_t t1 = clock();
    for (int i = 0; i < rozmiar; i++) {
        bool flaga = false;
        for (int j = 0; j <= rozmiar - 1; j++) {
            if (test[j] > test[j + 1]) {
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
    // clock_t t2 = clock();
    // double time = (t2-t1)/(double)CLOCKS_PER_SEC;
    // cout << "Czas wykonania: " << time << endl;
}
template <typename T>
void tablica<T>::dodajWiele(int ilosc) {
    // clock_t t1 = clock();
    for (int i = 0; i < ilosc; i++) {
        dodaj(rand() % 10000);
    }
    // clock_t t2 = clock();
    // double time = (t2-t1)/(double)CLOCKS_PER_SEC;
    // cout << "Czas wykonania: " << time << endl;
}

int main() {
    tablica<int> test;
    int wybor;
    for (;;) {
        cout << "1.Dodaj element" << endl;
        cout << "2.Zwroc dane konkretnego elementu" << endl;
        cout << "3.Zmiana danych elementu" << endl;
        cout << "4.Czyszczenie tablicy" << endl;
        cout << "5.Wypisanie wszystkich elementow" << endl;
        cout << "6.Sortowanie" << endl;
        cout << "7.Dodaj wiele elementow" << endl;
        cout << "0.Wyjdz" << endl;
        cout << "\n Co chcesz zrobic: ";
        cin >> wybor;

        if (wybor == 1) {
            cout << "Podaj wartosc ktora chcesz dodac do tablicy: ";
            cin >> test.data;
            clock_t t1 = clock();
            test.dodaj(test.data);
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
            system("pause");
        }
        else if (wybor == 2) {
            test.wyszukaj();
            system("pause");
        }
        else if (wybor == 3) {
            test.zmiana();
            system("pause");
        }
        else if (wybor == 4) {
            clock_t t1 = clock();
            test.czysc();
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
            system("pause");
        }
        else if (wybor == 5) {
            clock_t t1 = clock();
            test.wypisz();
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
            system("pause");
        }
        else if (wybor == 6) {
            clock_t t1 = clock();
            test.sort();
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
            system("pause");
        }
        else if (wybor == 7) {
            int ilosc = 0;
            cout << "Ile elementow chcesz dodac: ";
            cin >> ilosc;
            clock_t t1 = clock();
            test.dodajWiele(ilosc);
            clock_t t2 = clock();
            double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
            cout << "Czas wykonania: " << time << endl;
            system("pause");
        }
        else {
            break;
        }
        system("cls");
    }
    test.czysc();
    delete [] &test;
    return 0;
}