package org.example;
import java.util.*;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Persistence;
import jakarta.persistence.Query;

public class Main {
    public static void main(String[] args) {

        EntityManagerFactory emf = Persistence.createEntityManagerFactory("labs");
        EntityManager em = emf.createEntityManager();

        //Wyczyszczenie bazy danych
//        em.getTransaction().begin();
//        em.createNativeQuery("SET FOREIGN_KEY_CHECKS = 0").executeUpdate();
//        List<String> tableNames = em.createNativeQuery("SHOW TABLES").getResultList();
//        for (String tableName : tableNames) {
//            em.createNativeQuery("DROP TABLE IF EXISTS " + tableName).executeUpdate();
//        }
//        em.createNativeQuery("SET FOREIGN_KEY_CHECKS = 1").executeUpdate();
//        em.getTransaction().commit();


        Przedmiot matematyka = new Przedmiot("Matematyka 1A");
        Przedmiot fizyka = new Przedmiot("Fizyka 1A");
        Przedmiot chemia = new Przedmiot("Chemia 1A");
        Przedmiot biologia = new Przedmiot("Biologia 2A");
        Przedmiot geografia = new Przedmiot("Geografia 2A");
        Przedmiot historia = new Przedmiot("Historia 2A");

        Nauczyciel nauczyciel1 = new Nauczyciel("Jan", "Kowalski", "mgr");
        Nauczyciel nauczyciel2 = new Nauczyciel("Anna", "Nowak", "dr");
        Nauczyciel nauczyciel3 = new Nauczyciel("Piotr", "Wiśniewski", "prof");

        Uczen uczen1 = new Uczen("Jan", "Nowak", 12);
        Uczen uczen2 = new Uczen("Anna", "Kowalska", 12);
        Uczen uczen3 = new Uczen("Piotr", "Wiśniewski", 12);
        Uczen uczen4 = new Uczen("Krzysztof", "Kowalczyk", 12);
        Uczen uczen5 = new Uczen("Katarzyna", "Wiśniewska", 13);
        Uczen uczen6 = new Uczen("Marek", "Nowak", 13);
        Uczen uczen7 = new Uczen("Karolina", "Kowalska", 13);
        Uczen uczen8 = new Uczen("Kamil", "Kowalczyk", 13);

        Klasa klasa1 = new Klasa();
        klasa1.setNazwa("1A");
        klasa1.setPoziom(1);
        addKlasa(matematyka, fizyka, chemia, nauczyciel1, uczen1, uczen2, uczen3, uczen4, klasa1);


        Klasa klasa2 = new Klasa();
        klasa2.setNazwa("2A");
        klasa2.setPoziom(2);
        addKlasa(biologia, geografia, historia, nauczyciel2, uczen5, uczen6, uczen7, uczen8, klasa2);


        //Wgranie danych do bazy
        em.getTransaction().begin();
        em.persist(klasa1);
        em.persist(klasa2);
        em.getTransaction().commit();

        //dla wybranej osoby ucznia wyświetlić jej przedmioty wraz z nazwiskiem odpowiedzialnego nauczyciela
        String queryStr = "SELECT p.nazwa, n.nazwisko FROM Przedmiot p JOIN p.klasa k JOIN k.uczniowie u JOIN p.nauczyciel n WHERE u.id = :studentId";
        Query query = em.createQuery(queryStr);
        query.setParameter("studentId", uczen1.getId());

        List<Object[]> results = query.getResultList();
        for (Object[] result : results) {
            System.out.println("Subject: " + result[0] + ", Teacher: " + result[1]);
        }

        //dla wybranego nauczyciela wyświetlić wszystkich jego uczniów z klas, z którymi realizuje jakieś przedmioty.
        String queryStr2 = "SELECT u.imie, u.nazwisko FROM Uczen u JOIN u.klasa k JOIN k.przedmioty p JOIN p.nauczyciel n WHERE n.id = :teacherId GROUP BY u.id";
        Query query2 = em.createQuery(queryStr2);
        query2.setParameter("teacherId", nauczyciel1.getId());

        List<Object[]> results2 = query2.getResultList();
        for (Object[] result2 : results2) {
            System.out.println("Student: " + result2[0] + " " + result2[1]);
        }

        em.close();
        emf.close();
    }

    private static void addKlasa(Przedmiot przedmiot1, Przedmiot przedmiot2, Przedmiot przedmiot3, Nauczyciel nauczyciel, Uczen uczen1, Uczen uczen2, Uczen uczen3, Uczen uczen4, Klasa klasa) {
        uczen1.setKlasa(klasa);
        uczen2.setKlasa(klasa);
        uczen3.setKlasa(klasa);
        uczen4.setKlasa(klasa);
        nauczyciel.setKlasa(klasa);
        przedmiot1.setKlasa(klasa);
        przedmiot1.setNauczyciel(nauczyciel);
        przedmiot2.setKlasa(klasa);
        przedmiot2.setNauczyciel(nauczyciel);
        przedmiot3.setKlasa(klasa);
        przedmiot3.setNauczyciel(nauczyciel);
        klasa.setNauczyciel(nauczyciel);
        klasa.setUczniowie(new ArrayList<Uczen>());
        klasa.getUczniowie().add(uczen1);
        klasa.getUczniowie().add(uczen2);
        klasa.getUczniowie().add(uczen3);
        klasa.getUczniowie().add(uczen4);
        klasa.setPrzedmioty(new ArrayList<Przedmiot>());
        klasa.getPrzedmioty().add(przedmiot1);
        klasa.getPrzedmioty().add(przedmiot2);
        klasa.getPrzedmioty().add(przedmiot3);
    }
}