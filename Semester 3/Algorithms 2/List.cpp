#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <time.h> //pomiar czasowy wykonania operacji
#include <random>
using namespace std;

int pole1;
char pole2;
int id_usun;
int nr;
default_random_engine gen(time(nullptr));
uniform_int_distribution<int> dist(1,20);
int wybor =0;
int ilosc = 0;
char litery[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
// int cyfry[26] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 };


template <typename T, typename Y>
struct element {
    T pole1;
    Y pole2;
    element<T,Y>* poprzedni;
    element<T,Y>* nastepny;
    element() {
    nastepny = 0;
    poprzedni = 0;
}
};

template <typename T, typename Y>
struct lista {
    element<T,Y>* pierwszy;
    element<T,Y>* ostatni;
    void dodaj_poczatek(T pole1, Y pole2);//b †
    void dodaj_koniec(T pole1, Y pole2);//a †
    void dodaj_srodek(int id,T pole1, Y pole2);//i †
    void usun_pierwszy();//d † 
    void usun_srodek(int nr);//h †
    void usun_koniec();//c †
    void szukaj(int nr ); //e †
    void zamiana(int nr, T pole1, Y pole2); //f † 
    void czysc(); //usuniecie wszystkich elementow listy //j †
    void wyswietl_liste(); //k †
    void wyszukaj(); //g †
    int liczba_elementow=0;
    //! Testy
    void testy();
    void testDodaj(int ilosc);
    void testUsun(int ilosc);
    lista(){
    pierwszy = 0;
    ostatni = 0;
}};

template <typename T, typename Y>
void lista<T,Y>::dodaj_poczatek(T pole1, Y pole2) {
    element<T,Y>* nowy = new element<T,Y>;
    nowy->pole1 = pole1;
    nowy->pole2 = pole2;
    if (liczba_elementow==0)
    {
        pierwszy = nowy;
        ostatni = nowy;
    }
    else {
        nowy->nastepny = pierwszy;
        pierwszy->poprzedni = nowy;
        pierwszy=nowy;
    }
    liczba_elementow++;
}

template <typename T, typename Y>
void lista<T,Y>::dodaj_koniec(T pole1, Y pole2) {
    element<T,Y>* nowy = new element<T,Y>;
    nowy->pole1 = pole1;
    nowy->pole2 = pole2;
    if (liczba_elementow==0) {
        pierwszy = nowy;
        ostatni = nowy;
    }
    else {
        nowy->poprzedni = ostatni;
        ostatni->nastepny = nowy;
        ostatni = nowy;
    }
    liczba_elementow++;
}

template <typename T, typename Y>
void lista<T,Y>::dodaj_srodek(int id, T pole1, Y pole2) {
    element<T,Y>* temp = pierwszy;
    int j = 1;
    while (temp) // ustawienie wskaznika na osobie n-1
    {
        if (j == id-1) break;
        temp = temp->nastepny;
        j++;
    }
    element<T,Y>* nowy = new element<T,Y>;
    nowy->pole1 = pole1;
    nowy->pole2 = pole2;
    nowy->nastepny = temp->nastepny;
    temp->nastepny->poprzedni = nowy;
    temp->nastepny = nowy;
    nowy->poprzedni = temp;
    liczba_elementow++;
}

template <typename T, typename Y>
void lista<T,Y>::usun_pierwszy() {
    // usuniecie pierwszego elementu listy
    element<T,Y>* temp = pierwszy;
    if (liczba_elementow == 0) {
        cout << "Lista jest pusta" << endl;
    }
    else if (liczba_elementow == 1) {
        delete temp;
        liczba_elementow--;
    }
    else {
        pierwszy = temp->nastepny;
        pierwszy->poprzedni = nullptr;
        delete temp;
        liczba_elementow--;
    }
}

template <typename T, typename Y>
void lista<T,Y>::usun_srodek(int id_usun) {
    element<T,Y>* temp = pierwszy;
    if (liczba_elementow == 0)
    {
        cout << "Lista jest pusta" << endl;
    }
    else if (liczba_elementow == 1) {
        delete temp;
        liczba_elementow--;
    }
    else {
        if (id_usun == 1) {
            usun_pierwszy();
        }
        else if (id_usun == liczba_elementow) {
            usun_koniec();
        }
        else if(id_usun<liczba_elementow && id_usun>1){
            int j = 1;
            while (temp) // ustawienie wskaznika na osobie n-1
            {
                if ((j + 1) == id_usun) break;
                temp = temp->nastepny;
                j++;
            }
            // przesuniece wskaznikow by element n+1(np1) i n-1 wskazywaly teraz na siebie, usuniecie elementu n
            element<T,Y>* usuwany = temp->nastepny;
            temp->nastepny->nastepny->poprzedni = temp;
            temp->nastepny = temp->nastepny->nastepny;
            delete usuwany;
            liczba_elementow--;
        }
        else {
            cout << "Podany indeks wykracza poza zakres" << endl;
        }
    }
}

template <typename T, typename Y>
void lista<T,Y>::usun_koniec() {
    // usuniecie ostatniego elementu listy
    element<T,Y>* temp = ostatni;
    if (liczba_elementow == 0) {
        cout << "Lista jest pusta" << endl;
    }
    else if (liczba_elementow == 1) {
        delete temp;
        liczba_elementow--;
    }
    else {
        ostatni = temp->poprzedni;
        ostatni->nastepny = nullptr;
        delete temp;
        liczba_elementow--;
    }
}

template <typename T, typename Y>
void lista<T,Y>::czysc() {
    while (liczba_elementow != 0) {
        usun_pierwszy();
    }
}

template <typename T, typename Y>
void lista<T,Y>::wyswietl_liste()
{
    if (liczba_elementow == 0) {
        cout << "Lista jest pusta" << endl;
    }
    else {
        int id = 1;
        element<T,Y>* temp = pierwszy;
        while (id!=liczba_elementow+1) {
            cout << id << ". " << temp->pole1 << ":" << temp->pole2 << endl;
            temp = temp->nastepny;
            id++;
        }
    }
}

template <typename T, typename Y>
void lista<T,Y>::szukaj(int nr) {
    if (nr > 0 && nr < liczba_elementow) {
        if ((liczba_elementow - nr) >= (nr - 1)) {
            int id = 1;
            element<T,Y>* temp = pierwszy;
            while (id != nr + 1) {
                if (id == nr) {
                    cout << nr << ". " << temp->pole1 << ":" << temp->pole2 << endl;
                }
                temp = temp->nastepny;
                id++;
            }
        }
        else if ((liczba_elementow - nr) < (nr - 1)) {
            int id = liczba_elementow;
            element<T,Y>* temp = ostatni;
            while (id != nr - 1) {
                if (id == nr) {
                    cout << nr << ". " << temp->pole1 << ":" << temp->pole2 << endl;
                }
                temp = temp->poprzedni;
                id--;
            }
        }
    }
    else {
        cout << "Podany indeks wykracza poza zakres" << endl;
    }
}

template <typename T, typename Y>
void lista<T,Y>::zamiana(int nr, T pole1, Y pole2) {
    if (nr > 0 && nr < liczba_elementow) {
        if ((liczba_elementow - nr) >= (nr - 1)) {
            int id = 1;
            element<T,Y>* temp = pierwszy;
            while (id != nr + 1) {
                if (id == nr) {
                    temp->pole1 = pole1;
                    temp->pole2 = pole2;
                }
                temp = temp->nastepny;
                id++;
            }
        }
        else if ((liczba_elementow - nr) < (nr - 1)) {
            int id = liczba_elementow;
            element<T,Y>* temp = ostatni;
            while (id != nr - 1) {
                if (id == nr) {
                    temp->pole1 = pole1;
                    temp->pole2 = pole2;
                }
                temp = temp->poprzedni;
                id--;
            }
        }
     }
    else {
        cout << "Podany indeks wykracza poza zakres" << endl;
    }
}

template <typename T, typename Y>
void lista<T,Y>::wyszukaj() {
    int wybor;
    int indeks = 0;
    element<T,Y>* temp = pierwszy;
    element<T,Y>* szukany = new element<T,Y>;
    cout << "Wyszukujesz element za pomoca wartosci: pole1[1] czy pole2[2]?" << endl;
    cin >> wybor;
    switch (wybor){
        case 1:
            int wartosc1;
            cout << "Podaj wartosc pole1: ";
            cin >> wartosc1;
            for (int i = 0; i < liczba_elementow; i++) {
                if (temp->pole1 == wartosc1) {
                    cout << temp->pole1 << ":" << temp->pole2 << endl;
                    indeks++;
                }
                temp = temp->nastepny;
            }
            break;
        case 2:
            char wartosc2;
            cout << "Podaj wartosc pole2: ";
            cin >> wartosc2;
            for (int i = 0; i < liczba_elementow; i++) {
                if (temp->pole2 == wartosc2) {
                    cout << temp->pole1 << ":" << temp->pole2 << endl;
                    indeks++;
                }
                temp = temp->nastepny;
            }
            break;
        default:
            cout << "Podano bledna wartosc" << endl;
            break;
    }
}

//! Testy
//!
template <typename T, typename Y>
void lista<T,Y>::testy(){
    cout << "1.Test dodawania" << endl;
    cout << "2.Test usuwania" << endl;
    cout << "3.Test wyszukiwania" << endl;
    cout << "Ktory test chcesz wykonac: ";
    cin >> wybor;
    switch (wybor){
        case 1:
            cout << "Ile elementow chcesz dodac: ";
            cin >> ilosc;
            testDodaj(ilosc);
            break;
        case 2:
            cout << "Ile elementow chcesz usunac: ";
            cin >> ilosc;
            if(liczba_elementow<=ilosc){
                czysc();
                cout << "Podana ilosc jest wieksza od liczby elementow. Lista zostala wyczyszczona" << endl;
            }
            else{
                testUsun(ilosc);
            }
            break;
        default:
            break;
    }
}

template <typename T, typename Y>
void lista<T,Y>::testDodaj(int ilosc){
    clock_t t1 = clock();
    for(int i=0; i<=ilosc/2; i++){
        dodaj_koniec(rand()%10000,litery[rand()%26]);
    }
    for(int j=0; j<floor(ilosc/2); j++){
        dodaj_poczatek(rand()%10000,litery[rand()%26]);
    }
    clock_t t2 = clock();
    double time = (t2-t1)/(double)CLOCKS_PER_SEC;
    cout << "Czas wykonania: " << time << endl;
}

template <typename T, typename Y>
void lista<T,Y>::testUsun(int ilosc){
    clock_t t1 = clock();
    for(int i=0; i<=ilosc; i++){
        usun_srodek(rand()%liczba_elementow);
    }
    clock_t t2 = clock();
    double time = (t2-t1)/(double)CLOCKS_PER_SEC;
    cout << "Czas wykonania: " << time << endl;
}

int main() {
    lista<int,char>* test = new lista<int,char>;// tworzymy liste
    int user_choice = 0;
    for (;;) {
        cout << "1.Wyswietl liste" << endl;
        cout << "2.Dodaj element na poczatek" << endl;
        cout << "3.Dodaj element na koniec" << endl;
        cout << "4.Dodaj element w srodek listy" << endl;
        cout << "5.Usun element z poczatku" << endl;
        cout << "6.Usun element ze srodka" << endl;
        cout << "7.Usun element z konca" << endl;
        cout << "8.Liczba elementow" << endl;
        cout << "9.Wyczysc liste" << endl;
        cout << "10.Wyszukaj element" << endl;
        cout << "11.Zamiana danych elementu" << endl;
        cout << "12.Wyszukaj elementy po wartosci" << endl;
        cout << "13.Testy" << endl;
        cout << "0.Wyjdz" << endl;
        cout << "\nCo chcesz zrobic?: ";
        cin >> user_choice;
        cout << endl;

        if (user_choice == 1) {
            cout << "Lista elementow: " << endl;
            test->wyswietl_liste();
            system("pause");
            cout << endl;
        }
        else if (user_choice == 2) {
            cout << "Podaj wartosc pole1: ";
            cin >> pole1;
            cout << "Podaj wartosc pole2: ";
            cin >> pole2;
            test->dodaj_poczatek(pole1, pole2);
            system("pause");
            cout << endl;
        }
        else if (user_choice == 3) {
            cout << "Podaj wartosc pole1: ";
            cin >> pole1;
            cout << "Podaj wartosc pole2: ";
            cin >> pole2;
            test->dodaj_koniec(pole1, pole2);
            system("pause");
            cout << endl;
        }
        else if (user_choice == 4) {
            int wybor;
            if (test->liczba_elementow == 0) {
                cout << "Lista jest pusta" << endl;
            }
            else if (test->liczba_elementow == 1) {
                cout << "Lista zawiera 1 element." << endl;
                cout << "Chcesz dodac element na poczatek (1), czy koniec (2): ";
                cin >> wybor;
                if (wybor == 1) {
                    cout << "Podaj wartosc pole1: ";
                    cin >> pole1;
                    cout << "Podaj wartosc pole2: ";
                    cin >> pole2;
                    test->dodaj_poczatek(pole1, pole2);
                }
                else if (wybor == 2) {
                    cout << "Podaj wartosc pole1: ";
                    cin >> pole1;
                    cout << "Podaj wartosc pole2: ";
                    cin >> pole2;
                    test->dodaj_koniec(pole1, pole2);
                }
                else {
                    cout << "Podano bledna wartosc";
                }
            }
            else {
                int id;
                cout << "Podaj id nowego elementu: ";
                cin >> id;
                cout << "Podaj wartosc pole1: ";
                cin >> pole1;
                cout << "Podaj wartosc pole2: ";
                cin >> pole2;
                test->dodaj_srodek(id, pole1, pole2);
                system("pause");
                cout << endl;
            }
        }
        else if (user_choice == 5) {
            test->usun_pierwszy();
            system("pause");
            cout << endl;
        }
        else if (user_choice == 6) {
            test->wyswietl_liste();
            cout << "Podaj id elementu do usuniecia: ";
            cin >> id_usun;
            test->usun_srodek(id_usun);
            system("pause");
            cout << endl;
        }
        else if (user_choice == 7) {
            test->usun_koniec();
            system("pause");
            cout << endl;
        }
        else if (user_choice == 8) {
            // test->liczba_elementow();
            cout << test->liczba_elementow << endl;
            system("pause");
            cout << endl;
        }
        else if (user_choice == 9) {
            test->czysc();
            system("pause");
            cout << endl;
        }
        else if (user_choice == 10) {
            if (test->liczba_elementow == 0) {
                cout << "Lista jest pusta" << endl;
            }
            else {
                cout << "Podaj numer szukanego elementu: ";
                cin >> nr;
                test->szukaj(nr);
            }
            system("pause");
        }
        else if (user_choice == 11) {
            if (test->liczba_elementow == 0) {
                cout << "Lista jest pusta" << endl;
            }
            else {
                cout << "Podaj numer elementu ktorego dane chcesz zmienic: ";
                cin >> nr;
                cout << "Podaj nowa wartosc pole1: ";
                cin >> pole1;
                cout << "Podaj nowa wartosc pole2: ";
                cin >> pole2;
                test->zamiana(nr, pole1, pole2);
            }
            system("pause");
        }
        else if (user_choice == 12) {
            if (test->liczba_elementow == 0) {
                cout << "Lista jest pusta" << endl;
            }
            else {
                test->wyszukaj();
            }
            system("pause");
        }
        else if(user_choice==13){
            test->testy();
            system("pause");
        }
        else{
            //cout << "Podano bledna wartosc";
            break;
        }
        system("cls");
    }
    test->czysc();
    delete test;
    return 0;
}