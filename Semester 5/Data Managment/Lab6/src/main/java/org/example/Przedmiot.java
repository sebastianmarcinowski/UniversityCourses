package org.example;
import jakarta.persistence.*;
import java.io.Serializable;

@Entity
public class Przedmiot implements Serializable{
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String nazwa;
    @ManyToOne(cascade = CascadeType.ALL)
    private Nauczyciel nauczyciel;
    @ManyToOne(cascade = CascadeType.ALL)
    private Klasa klasa;

    public Przedmiot() {
    }
    public Przedmiot(String nazwa) {
        this.nazwa = nazwa;
    }

    public Nauczyciel getNauczyciel(){return nauczyciel;}
    public void setNauczyciel(Nauczyciel nauczyciel){this.nauczyciel = nauczyciel;}

    public Klasa getKlasa(){return klasa;}
    public void setKlasa(Klasa klasa){this.klasa = klasa;}

    public Long getId() {return id;}
    public void setId(Long id) {this.id = id;}

    public String getNazwa() {return nazwa;}
    public void setNazwa(String nazwa) {this.nazwa = nazwa;}
}
