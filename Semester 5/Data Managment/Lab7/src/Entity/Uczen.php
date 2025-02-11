<?php

namespace App\Entity;

use Doctrine\ORM\Mapping as ORM;

/**
 * @ORM\Entity
 */
class Uczen
{
    /**
     * @ORM\Id
     * @ORM\GeneratedValue(strategy="AUTO")
     * @ORM\Column(type="integer")
     */
    private $id;

    /**
     * @ORM\Column(type="string", length=255)
     */
    private $imie;

    /**
     * @ORM\Column(type="string", length=255)
     */
    private $nazwisko;

    /**
     * @ORM\Column(type="integer")
     */
    private $wiek;

    /**
     * @ORM\ManyToOne(targetEntity="Klasa", cascade={"persist", "remove"})
     * @ORM\JoinColumn(name="klasa_id", referencedColumnName="id", nullable=true)
     */
    private $klasa;

    public function __construct(string $imie = null, string $nazwisko = null, int $wiek = null)
    {
        $this->imie = $imie;
        $this->nazwisko = $nazwisko;
        $this->wiek = $wiek;
    }

    public function getId()
    {
        return $this->id;
    }

    public function setId(int $id)
    {
        $this->id = $id;
    }

    public function getImie()
    {
        return $this->imie;
    }

    public function setImie(string $imie)
    {
        $this->imie = $imie;
    }

    public function getNazwisko()
    {
        return $this->nazwisko;
    }

    public function setNazwisko(string $nazwisko)
    {
        $this->nazwisko = $nazwisko;
    }

    public function getWiek()
    {
        return $this->wiek;
    }

    public function setWiek(int $wiek)
    {
        $this->wiek = $wiek;
    }

    public function getKlasa()
    {
        return $this->klasa;
    }

    public function setKlasa(?Klasa $klasa)
    {
        $this->klasa = $klasa;
    }
}
?>