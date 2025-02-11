#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

int indeks = 1;
int user_choice;
string name;
string surname;
int age;
int delete_choice;
fstream plik;

// utworzenie struktury pojedynczej osoby
struct osoba
{
    string imie;
    string nazwisko;
    int wiek;
    osoba *next;
    osoba();
};

osoba::osoba()
{
    next = 0;
}

// utworzenie struktury listy
struct lista
{
    osoba *pierwsza;
    void dodaj(string imie,string nazwisko,int wiek);
    void usun(int nr);
    void wyswietl_liste();
	void wyszukaj();
	int liczba_elementow();
	void zapis();
    lista();
};

lista::lista()
{
    pierwsza = 0;
}

void lista::dodaj(string imie, string nazwisko, int wiek)
{
	osoba *nowa = new osoba; 

	nowa->imie = imie;
	nowa->nazwisko = nazwisko;
	nowa->wiek = wiek;
	if (pierwsza==0) //sprawdzanie czy to pierwszy element listy
	{
		pierwsza = nowa;
	}
	else
	{
		// znalezienie wskaznika ostatniego elementu listy
		osoba *temp = pierwsza;

		while (temp->next)
		{
			temp = temp->next;
		}

		temp->next = nowa; // ostatni element wskazuje na nasz nowy
	}
}

void lista::wyswietl_liste()
{
    // wskaznik na pierszy element listy
	osoba *temp = pierwsza;
	plik.open("wizytowka2.txt", ios::in);
    if(plik.good()==false)
    {
        cout << "Plik nie istnieje";
        exit(0);
    }
    string linia;
	string *wskaznik;
	string wynik;
    while (getline(plik,linia))
    {   
		// cout << indeks << ". Imie: " << temp->imie << " Nazwisko: " << temp->nazwisko << " Wiek: "<< temp->wiek << endl;
		wskaznik = &linia;
		string value;
		value = *wskaznik;
		cout << value << endl;
		
		indeks++;
    }
    plik.close();
	indeks = 1;
}

void lista::usun(int nr)
{
 // jezeli to pierwszy element listy
	if (nr==1)
	{
		osoba *temp = pierwsza;
		pierwsza = temp->next; //ustawiamy poczatek na drugi element
		delete temp; // usuwamy stary pierwszy element z pamieci
	}
	else if (nr>=2)
	{
		int j = 1;
		// wskaznik *temp bedzie wskaznikiem na osobe poprzedzajaca osobe usuwana
		osoba *temp = pierwsza;

		while (temp)
		{
			// sprawdzamy czy wskaznik jest na osobie poprzedniej niz usuwana
			if ((j+1)==nr) break;

			// jezeli nie to przewijamy petle do przodu
			temp = temp->next;
			j++;
		}

		// wskaznik *temp wskazuje teraz na osobe n-1
		// nadpisujemy wkaznik n-1 z osoby n na osobe n+1
		// bezpowrotnie tracimy osobe n-ta

		// jezeli usuwamy ostatni element listy
		if (temp->next ->next==0) {
			delete temp->next;
			temp->next = 0;
		}
		// jezeli usuwamy srodkowy element
		else {
			osoba *usuwana = temp->next;
			temp->next = temp->next->next;
			delete usuwana;
		}
	}
}
int lista::liczba_elementow()
{
	osoba*temp=pierwsza;
	int liczba_elementow = 0;
	while(temp)
	{
		liczba_elementow++;
		temp=temp->next;
	}
	return liczba_elementow;
}
void lista::wyszukaj()
{
	osoba *temp = pierwsza;
	int wybor = 0;
	string wyszukaj_po;
	for (;;)
	{
		cout << "Wedle czego chcesz wyszukac uzytkownika:\n1. Imie.\n2. Nazwisko.\n3. Wiek." << endl;
		cin >> wybor;

		if(wybor == 1)//wyszukiwanie po imieniu
		{ 
			cout << "Podaj imie do wyszukania: ";
			cin >> wyszukaj_po;
			while(temp)
			{	
				if(wyszukaj_po==temp->imie)
				{
					cout << indeks << ". Imie: " << temp->imie << " Nazwisko: " << temp->nazwisko << " Wiek: "<< temp->wiek << endl;
				}
				temp = temp -> next;
			}
			break;
		}
		else if(wybor == 2)//wyszukiwanie po nazwisku
		{
			cout << "Podaj nazwisko do wyszukania: ";
			cin >> wyszukaj_po;
			while(temp)
			{	
				if(wyszukaj_po==temp->nazwisko)
				{
					cout << indeks << ". Imie: " << temp->imie << " Nazwisko: " << temp->nazwisko << " Wiek: "<< temp->wiek << endl;
				}
				temp = temp -> next;
			}
			break;
		}
		else if (wybor==3)//wyszukiwanie po wieku
		{
			cout << "Podaj wiek do wyszukania: ";
			cin >> wyszukaj_po;
			while(temp)
			{	
				if(wyszukaj_po==to_string(temp->wiek))
				{
					cout << indeks << ". Imie: " << temp->imie << " Nazwisko: " << temp->nazwisko << " Wiek: "<< temp->wiek << endl;
				}
				temp = temp -> next;
			}
			break;
		}
		else
		{
			cout << "Podano bledna wartosc" << endl;
			break;
		}
	}
}
void lista::zapis()
{
	osoba *temp = pierwsza;
	plik.open("wizytowka2.txt", ios::out);
	if (plik.good()==false)
	{
		cout << "Plik nie istnieje!" << endl;
		exit(0);
	}
	while(temp)
	{
		plik << temp << endl;
		temp = temp->next;
	}
	plik.close();
}
int main()
{
	lista *uzytkownicy = new lista; // tworzymy liste
	// dodajemy rekordy do bazy
	uzytkownicy->dodaj("Maciej","Nowak", 23);
	uzytkownicy->dodaj("Arkadiusz","Kowalski", 44);
	uzytkownicy->dodaj("Dariusz","Nosek", 19);
	uzytkownicy->dodaj("Andrzej","Gwizd", 21);
	uzytkownicy->dodaj("Jozek","Griffin", 22);

    for(;;)
    {
        cout << "1.Wyswietl liste uzytkownikow." << endl;
        cout << "2.Dodaj uzytkownika do listy." << endl;
        cout << "3.Usun uzytkownika z listy." << endl;
		cout << "4.Wyszukaj uzytkownikow." << endl;
        cout << "5.Wyjdz" << endl;

        cout << "\nCo chcesz zrobic?: ";
        cin >> user_choice;
        cout << endl;

        if(user_choice==1)
        {
            cout << "Uzytkownicy: " << endl;
            uzytkownicy->wyswietl_liste();
			uzytkownicy->zapis();
            system("pause");
            cout << endl;
        }
        else if(user_choice==2)
        {
			cout << "Podaj imie: " << endl;
			cin >> name;
			cout << "Podaj nazwisko: " << endl;
			cin >> surname;
			cout << "Podaj wiek: "<< endl;
			cin >> age;
            uzytkownicy->dodaj(name,surname,age);
			uzytkownicy->zapis();
            system("pause");
            cout << endl;
        }
        else if(user_choice==3)
        {
            uzytkownicy->wyswietl_liste();
			cout << "Podaj numer osoby do usuniecia: " << endl;
			cin >> delete_choice;
            uzytkownicy->usun(delete_choice);
			uzytkownicy->zapis();
            system("pause");
            cout << endl;
        }
        else if(user_choice==4)
        {
            uzytkownicy ->wyszukaj();
			system("pause");
        }
		else if(user_choice==5)
		{
			return 0;
		}
        else
        {
            cout << "Podano bledna wartosc";
            break;
        }
        system("cls");
    }
	
	delete uzytkownicy;
 	system("pause >nul");

	return 0;
}