package org.example;
import jakarta.persistence.*;
import java.util.List;
import java.io.Serializable;

@Entity
public class Klasa implements Serializable{
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String nazwa;
    private int poziom;
    @OneToOne(cascade = CascadeType.ALL)
    private Nauczyciel nauczyciel;
    @OneToMany(cascade = CascadeType.ALL)
    private List<Uczen> uczniowie;
    @OneToMany(cascade = CascadeType.ALL)
    private List<Przedmiot> przedmioty;

    public Nauczyciel getNauczyciel() {return nauczyciel;}
    public void setNauczyciel(Nauczyciel nauczyciel) {this.nauczyciel = nauczyciel;}

    public List<Uczen> getUczniowie() {return uczniowie;}
    public void setUczniowie(List<Uczen> uczniowie) {this.uczniowie = uczniowie;}

    public List<Przedmiot> getPrzedmioty() {return przedmioty;}
    public void setPrzedmioty(List<Przedmiot> przedmioty) {this.przedmioty = przedmioty;}

    public Long getId() {return id;}
    public void setId(Long id) {this.id = id;}

    public String getNazwa() {return nazwa;}
    public void setNazwa(String nazwa) {this.nazwa = nazwa;}

    public int getPoziom() {return poziom;}
    public void setPoziom(int poziom) {this.poziom = poziom;}
}