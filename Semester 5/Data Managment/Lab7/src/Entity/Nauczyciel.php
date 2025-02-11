<?php

namespace App\Entity;

use Doctrine\ORM\Mapping as ORM;
use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\Common\Collections\Collection;

/**
 * @ORM\Entity
 */
class Nauczyciel
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
     * @ORM\Column(type="string", length=255)
     */
    private $tytul;
    /**
     * @ORM\OneToMany(targetEntity="Przedmiot", mappedBy="nauczyciel", cascade={"persist", "remove"})
     */
    private $przedmioty;

    /**
     * @ORM\OneToOne(targetEntity="Klasa", cascade={"persist", "remove"})
     * @ORM\JoinColumn(name="klasa_id", referencedColumnName="id")
     */
    private $klasa;

    public function __construct(string $imie = null, string $nazwisko = null, string $tytul = null)
    {
        $this->imie = $imie;
        $this->nazwisko = $nazwisko;
        $this->tytul = $tytul;
        $this->przedmioty = new ArrayCollection();
    }

    public function getId(): ?int
    {
        return $this->id;
    }

    public function setId(int $id): void
    {
        $this->id = $id;
    }

    public function getImie(): ?string
    {
        return $this->imie;
    }

    public function setImie(string $imie): void
    {
        $this->imie = $imie;
    }

    public function getNazwisko(): ?string
    {
        return $this->nazwisko;
    }

    public function setNazwisko(string $nazwisko): void
    {
        $this->nazwisko = $nazwisko;
    }

    public function getTytul(): ?string
    {
        return $this->tytul;
    }

    public function setTytul(string $tytul): void
    {
        $this->tytul = $tytul;
    }

    /**
     * @return Collection|Przedmiot[]
     */
    public function getPrzedmioty(): Collection
    {
        return $this->przedmioty;
    }

    public function addPrzedmiot(Przedmiot $przedmiot): void
    {
        if (!$this->przedmioty->contains($przedmiot)) {
            $this->przedmioty[] = $przedmiot;
            $przedmiot->setNauczyciel($this);
        }
    }

    public function removePrzedmiot(Przedmiot $przedmiot): void
    {
        if ($this->przedmioty->removeElement($przedmiot)) {
            if ($przedmiot->getNauczyciel() === $this) {
                $przedmiot->setNauczyciel(null);
            }
        }
    }

    public function getKlasa(): ?Klasa
    {
        return $this->klasa;
    }

    public function setKlasa(Klasa $klasa): void
    {
        $this->klasa = $klasa;
    }
}
?>