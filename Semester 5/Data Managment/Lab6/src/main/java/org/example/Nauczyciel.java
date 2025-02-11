package org.example;
import jakarta.persistence.*;
import java.util.List;
import java.io.Serializable;

@Entity
public class Nauczyciel implements Serializable{
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String imie;
    private String nazwisko;
    private String tytul;
    @OneToMany(cascade = CascadeType.ALL)
    private List<Przedmiot> przedmioty;
    @OneToOne(cascade = CascadeType.ALL)
    private Klasa klasa;

    public Nauczyciel() {
    }
    public Nauczyciel(String imie, String nazwisko, String tytul) {
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.tytul = tytul;
    }

    public List<Przedmiot> getPrzedmioty() {return przedmioty;}
    public void setPrzedmioty(List<Przedmiot> przedmioty) {this.przedmioty = przedmioty;}

    public Klasa getKlasa() {return klasa;}
    public void setKlasa(Klasa klasa) {this.klasa = klasa;}

    public Long getId() {return id;}
    public void setId(Long id) {this.id = id;}

    public String getImie() {return imie;}
    public void setImie(String imie) {this.imie = imie;}

    public String getNazwisko() {return nazwisko;}
    public void setNazwisko(String nazwisko) {this.nazwisko = nazwisko;}

    public String  getTytul() {return tytul;}
    public void setTytul(String tytul) {this.tytul = tytul;}
}
