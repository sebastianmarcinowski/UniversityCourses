package org.example;
import jakarta.persistence.*;
import java.io.Serializable;

@Entity
public class Uczen implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String imie;
    private String nazwisko;
    private int wiek;
    @ManyToOne(cascade = CascadeType.ALL)
    private Klasa klasa;

    public Uczen() {
    }
    public Uczen(String imie, String nazwisko, int wiek) {
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.wiek = wiek;
    }

    public Klasa getKlasa(){return klasa;}
    public void setKlasa(Klasa klasa){this.klasa = klasa;}

    public Long getId() {return id;}
    public void setId(Long id) {this.id = id;}

    public String getImie() {return imie;}
    public void setImie(String imie) {this.imie = imie;}

    public String getNazwisko() {return nazwisko;}
    public void setNazwisko(String nazwisko) {this.nazwisko = nazwisko;}

    public int getWiek() {return wiek;}
    public void setWiek(int wiek) {this.wiek = wiek;}
}
