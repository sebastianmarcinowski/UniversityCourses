#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

//TODO: dodac zapis odczyt z pliku, multimapa i dziedziczenie(moze byc osobny program)

// Tworzenie klasy Car wraz z konstruktorami do tworzenia obiektów oraz funkcji zapisu i odczytu danych
class Pojazd{
    private:
        // virtual void funkcja();
        virtual void wyjscie(){};
        virtual void wejscie(){};
};
class Car : public Pojazd{
    public:
        std::string marka;
        std::string model;
        std::string kolor;
        std::string typ_nadwozia;
        int rok_produkcji;
        float cena;

        Car(){
            marka = "Brak";
            model = "Brak";
            kolor = "Brak";
            typ_nadwozia = "Brak";
            rok_produkcji = 0;
            cena = 0;
        };
        Car(std::string marka, std::string model, std::string kolor, std::string typ_nadwozia, int rok_produkcji, float cena){
            this->marka = marka;
            this->model = model;
            this->kolor = kolor;
            this->typ_nadwozia = typ_nadwozia;
            this->rok_produkcji = rok_produkcji;
            this->cena = cena;
        };
        void wyjscie(std::ostream& outs);
        void wejscie(std::istream& ins);   
};
// Utworznie strumienia odczytu i zapisu
std::ostream& operator << (std::ostream& odczyt,Car& tmp);
std::istream& operator >> (std::istream& zapis,Car& tmp);

// Zmienne globalne
    Car emp;
    std::vector <Car> cars;
    int indeks = 1;
    std::multimap <std::string,Car> mapa;
    std::fstream plik;

// funkcja do odczytu atrybutow obiektu
void Car::wyjscie(std::ostream& outs){
    std::cout << std::endl;
    std::cout << "Auto numer: " << indeks << ":" << std::endl;
    std::cout << "Marka: " << marka << std::endl; 
    std::cout << "Model: " << model << std::endl;
    std::cout << "Kolor: " << kolor << std::endl;
    std::cout << "Typ nadwozia: " << typ_nadwozia << std::endl;
    std::cout << "Rok produkcji: " << rok_produkcji << std::endl; 
    std::cout << "Cena: " << cena << std::endl;
    indeks++;
}
// funkcja do zapisu nowego obiektu
void Car::wejscie(std::istream& ins){
    std::cout << "Podaj marke: ";
    std::cin >> marka;
    std::cout << "Podaj model: ";
    std::cin >> model;
    std::cout << "Podaj kolor: ";
    std::cin >> kolor;
    std::cout << "Podaj typ nadwozia: ";
    std::cin >> typ_nadwozia;
    std::cout << "Podaj rok produkcji: ";
    std::cin >> rok_produkcji;
    std::cout << "Podaj cene: ";
    std::cin >> cena;
    system("pause");
    system("cls");
    
}
std::ostream& operator << (std::ostream& outs,Car& tmp){
    tmp.wyjscie(outs);
    return outs;
};
std::istream& operator >> (std::istream& ins,Car& tmp){
    tmp.wejscie(ins);
    return ins;
};

// Tworzenie obiektów i dodawanie ich do wektora
void dodaj(){
    std::cin >> emp;
    cars.push_back(emp);
    mapa.insert({emp.marka,emp});
    // plik.open("baza.txt", std::ios::out);
    // plik.write((char*)&emp, sizeof(emp));
    // for(int i=0; i<cars.size(); i++){
    //         plik << cars[i] << std::endl;
    //     }
    // plik.close();
}

// Wyswietlanie obietków i ich atrybutow z wektora
void wyswietl(){
    if(cars.size()==0){
        std::cout << "Baza jest pusta!" << std::endl;
    }
    else{
        for(int i=0; i<cars.size(); i++){
            std::cout << cars[i];
        }
    }
    indeks=1;

    // plik.open("baza.txt", std::ios::in);
    // plik.seekg(0);
    // plik.read((char*)&emp, sizeof(emp));
    // std::cout << "Marka " << emp.marka << std::endl;
    // std::cout << "Model " << emp.model << std::endl;
    // std::cout << "Kolor " << emp.kolor << std::endl;
    // std::cout << "Typ nadwozia " << emp.typ_nadwozia << std::endl;
    // std::cout << "Rok produkcji " << emp.rok_produkcji << std::endl;
    // std::cout << "Cena " << emp.cena << std::endl;
    // plik.close();
}

// Usuwanie obiektów z wektora na podstawie indeksu
void usun(){
    int curr_size = cars.size();
    // Spradzanie czy baza jest pusta jesli nie podajemy indeks auta do usunienia
    if(cars.size()==0){
        std::cout << "Baza jest pusta. Nie ma czego usuwac.";
    }
    else{
        int id_usun;
        std::cout << "Podaj indeks samochodu do usuniecia: ";
        std::cin >> id_usun;
        cars.erase(cars.begin()+id_usun-1);
    }
    // Sprawdzanie czy usuwanie powiodło sie
    if(curr_size != cars.size()){
        std::cout << "Operacja zakoncona pomyslnie";
    }
    else{
        std::cout << "Operacja zakonczona niepowodzeniem";
    }
}

// Wyszukiwanie obiektu na podstawie jednego z atrybutow
void wyszukaj(){
    int filtr;
    std::cout << "Wybierz filtr wyszukiwania: " << std::endl;
    std::cout << "1. Marka" << std::endl;
    std::cout << "2. Model" << std::endl;
    std::cout << "3. Kolor" << std::endl;
    std::cout << "4.Rodzaj nadwozia" << std::endl;
    std::cout << "5.Cena" << std::endl;
    std::cin >> filtr;
    
    if(filtr==1){
        std::string filtr_marka;
        std::cout << "Podaj szukana marke: " << std::endl;
        std::cin >> filtr_marka;

        for (auto itr = mapa.begin(); itr != mapa.end(); itr++)   
        if (itr -> first == filtr_marka)       
            std::cout << "Szukana marka: " << itr -> first << "  " << itr -> second << std::endl;
    }
    else if(filtr==2){
        std::string filtr_model;
        std::cout << "Podaj szukany model: " << std::endl;
        std::cin >> filtr_model;
        for(int i=0; i<cars.size();i++){
            if(cars[i].model==filtr_model){
                std::cout << cars[i];
            }
        }
    }
    else if(filtr==3){
        std::string filtr_kolor;
        std::cout << "Podaj szukany kolor: " << std::endl;
        std::cin >> filtr_kolor;
        for(int i=0; i<cars.size();i++){
            if(cars[i].kolor==filtr_kolor){
                std::cout << cars[i];
            }
        }
    }
    else if(filtr==4){
        std::string filtr_nadwozie;
        std::cout << "Podaj szukany typ nadwozia: " << std::endl;
        std::cin >> filtr_nadwozie;
        for(int i=0; i<cars.size();i++){
            if(cars[i].typ_nadwozia==filtr_nadwozie){
                std::cout << cars[i];
            }
        }
    }
    else if(filtr==5){
        int min_cena, max_cena;
        std::cout << "Podaj cene minimalna: ";
        std::cin >> min_cena;
        std::cout << "Podaj cene maksymalna: ";
        std::cin >> max_cena;
        for(int i=0; i<cars.size();i++){
            if(cars[i].cena>=min_cena && cars[i].cena<=max_cena){
                std::cout << cars[i];
            }
        }
    }
    else if(filtr==6){
        int min_rok, max_rok;
        std::cout << "Podaj zakres lat:";
        std::cout << "Od: ";
        std::cin >> min_rok;
        std::cout << "Do :";
        std::cin >> max_rok;
        for(int i=0; i<cars.size();i++){
            if(cars[i].rok_produkcji>=min_rok && cars[i].rok_produkcji<=max_rok){
                std::cout << cars[i];
            }
        }
    }
    else{
        std::cout << "Podano bledna wartosc" << std::endl;
    }
    indeks=1;
}

int main(){
    int user_choice;
    for(;;){
        std::cout << "1. Wyswietl baze samochodow" << std::endl;
        std::cout << "2. Dodaj samochod do bazy" << std::endl;
        std::cout << "3. Usun samochod z bazy" << std::endl;
        std::cout << "4. Wyszukaj samochod" << std::endl;
        std::cout << "5. Wyjdz" << std::endl;
        std::cout << "Co chcesz zrobic?: ";
        std::cin >> user_choice;
        std::cout << std::endl;

        if(user_choice==1){
            wyswietl();
            system("pause");
        }
        else if(user_choice==2){
            dodaj();
        }
        else if(user_choice==3){
            wyswietl();
            usun();
            system("pause");
        }
        else if(user_choice==4){
            wyszukaj();
            system("pause");
        }
        else if(user_choice==5){
            cars.clear();
            mapa.clear();

			return 0;
		}
        else{
            std::cout << "Podano bledna wartosc";
            break;
        }
        system("cls");
    }
    return 0;
}
