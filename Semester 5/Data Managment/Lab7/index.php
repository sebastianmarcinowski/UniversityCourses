<?php
require_once __DIR__ . '/bootstrap.php';
require_once __DIR__ . '/vendor/autoload.php';
//$em = getEntityManager();
function addKlasa($klasa, $uczen1, $uczen2, $uczen3, $uczen4, $przedmiot1, $przedmiot2, $przedmiot3, $wychowawca){
    $uczen1->setKlasa($klasa);
    $uczen2->setKlasa($klasa);
    $uczen3->setKlasa($klasa);
    $uczen4->setKlasa($klasa);
    $wychowawca->setKlasa($klasa);
    $przedmiot1->setKlasa($klasa);
    $przedmiot1->setNauczyciel($wychowawca);
    $przedmiot2->setKlasa($klasa);
    $przedmiot2->setNauczyciel($wychowawca);
    $przedmiot3->setKlasa($klasa);
    $przedmiot3->setNauczyciel($wychowawca);
    $klasa->addUczen($uczen1);
    $klasa->addUczen($uczen2);
    $klasa->addUczen($uczen3);
    $klasa->addUczen($uczen4);
    $klasa->addPrzedmiot($przedmiot1);
    $klasa->addPrzedmiot($przedmiot2);
    $klasa->addPrzedmiot($przedmiot3);
    $klasa->setNauczyciel($wychowawca);
}

$matematyka = new \App\Entity\Przedmiot('Matematyka');
$fizyka = new \App\Entity\Przedmiot('Fizyka');
$informatyka = new \App\Entity\Przedmiot('Informatyka');
$chemia = new \App\Entity\Przedmiot('Chemia');
$historia = new \App\Entity\Przedmiot('Historia');
$biologia = new \App\Entity\Przedmiot('Biologia');

$nauczyciel1 = new \App\Entity\Nauczyciel('Jan', 'Kowalski', 'mgr');
$nauczyciel2 = new \App\Entity\Nauczyciel('Anna', 'Nowak', 'mgr');
$nauczyciel3 = new \App\Entity\Nauczyciel('Piotr', 'Wiśniewski', 'mgr');

$uczen1 = new \App\Entity\Uczen('Jan', 'Kowalski', 15);
$uczen2 = new \App\Entity\Uczen('Anna', 'Nowak', 15);
$uczen3 = new \App\Entity\Uczen('Piotr', 'Wiśniewski', 15);
$uczen4 = new \App\Entity\Uczen('Krzysztof', 'Kowalczyk', 15);
$uczen5 = new \App\Entity\Uczen('Katarzyna', 'Wójcik', 15);
$uczen6 = new \App\Entity\Uczen('Marek', 'Kamiński', 15);
$uczen7 = new \App\Entity\Uczen('Karolina', 'Lewandowska', 15);
$uczen8 = new \App\Entity\Uczen('Michał', 'Zieliński', 15);

$klasa1 = new \App\Entity\Klasa('1A', 1);
addKlasa($klasa1, $uczen1, $uczen2, $uczen3, $uczen4, $matematyka, $fizyka, $informatyka, $nauczyciel1);
$klasa2 = new \App\Entity\Klasa('1B', 1);
addKlasa($klasa2, $uczen5, $uczen6, $uczen7, $uczen8, $chemia, $historia, $biologia, $nauczyciel2);

$em->persist($klasa1);
$em->persist($klasa2);
$em->flush();

// For the selected student, display their subjects along with the surname of the responsible teacher
$studentId = $uczen1->getId();
$queryStr = "SELECT p.nazwa, n.nazwisko 
             FROM App\Entity\Przedmiot p 
             JOIN p.klasa k 
             JOIN k.uczniowie u 
             JOIN p.nauczyciel n 
             WHERE u.id = :studentId";
$query = $em->createQuery($queryStr);
$query->setParameter('studentId', $studentId);

$results = $query->getResult();
foreach ($results as $result) {
    echo "Subject: " . $result['nazwa'] . ", Teacher: " . $result['nazwisko'] . "\n";
}

// For the selected teacher, display all their students from the classes with which they teach any subjects
$teacherId = $nauczyciel1->getId();
$queryStr2 = "SELECT u.imie, u.nazwisko 
              FROM App\Entity\Uczen u 
              JOIN u.klasa k 
              JOIN k.przedmioty p 
              JOIN p.nauczyciel n 
              WHERE n.id = :teacherId 
              GROUP BY u.id";
$query2 = $em->createQuery($queryStr2);
$query2->setParameter('teacherId', $teacherId);

$results2 = $query2->getResult();
foreach ($results2 as $result2) {
    echo "Student: " . $result2['imie'] . " " . $result2['nazwisko'] . "\n";
}
?>