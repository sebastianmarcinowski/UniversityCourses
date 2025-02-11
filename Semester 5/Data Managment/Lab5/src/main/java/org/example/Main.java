package org.example;
import java.util.*;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Persistence;
import jakarta.persistence.Query;

import java.util.Random;

public class Main {
    public static void main(String[] args) {
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("labs");
        EntityManager em = emf.createEntityManager();
        String[] names = {"Arek","Beata","Marek","Czarek","Ivan","Monika","Kasia"};
        String[] familyNames = {"Kowalska","Janik","Nowak","Wilczur","Cypek","Kociolek","Wazon"};

        //Wyczyszczenie bazy danych
        em.getTransaction().begin();

        // JPQL delete query without a WHERE clause
        Query delquery = em.createQuery("DELETE FROM Person p");
        int rowsDeleted = delquery.executeUpdate();
        em.getTransaction().commit();


        //Wczytanie danych do bazy
        for(int i=0; i<names.length; i++){
            Person person = new Person();
            int randAge = new Random().nextInt(1,50);
            person.setFirstName(names[i]);
            person.setFamilyName(familyNames[i]);
            person.setAge(randAge);
            em.getTransaction().begin();
            em.persist(person);
            em.getTransaction().commit();
        }

        //Wczytanie danych z bazy
        Query q = em.createQuery("select p from Person p");
        List<Person> people = q.getResultList();
        for(Person p : people){
            System.out.println(p.getId() + " " + p.getFirstName() + " " + p.getFamilyName() + " " + p.getAge());
        }
        System.out.println("---------------------------------------------------------");

        //W przypadku gdy wartość pola age danego obiektu jest mniejsza od 18 poprawić ją na 18 i zapisać.
        for(Person p : people){
            if(p.getAge() < 18 ){
                p.setAge(18);
            }
        }
        Query q2 = em.createQuery("select p from Person p");
        List<Person> people2 = q.getResultList();
        for(Person p : people2){
            System.out.println(p.getId() + " " + p.getFirstName() + " " + p.getFamilyName() + " " + p.getAge());
        }
        System.out.println("---------------------------------------------------------");
        //Podpunkt 5
        Query q3 = em.createQuery("select p from Person p WHERE p.age > 25");
        List<Person> people3 = q3.getResultList();
        System.out.println("Liczba osob powyzej 25 roku zycia: " + people3.size());

        em.close();
    }
}