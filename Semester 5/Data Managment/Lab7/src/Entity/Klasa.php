<?php

namespace App\Entity;

use Doctrine\ORM\Mapping as ORM;
use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\Common\Collections\Collection;

/**
 * @ORM\Entity
 */
class Klasa
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
    private $nazwa;

    /**
     * @ORM\Column(type="integer")
     */
    private $poziom;

    /**
     * @ORM\OneToOne(targetEntity="Nauczyciel", cascade={"persist", "remove"})
     * @ORM\JoinColumn(name="nauczyciel_id", referencedColumnName="id")
     */
    private $nauczyciel;

    /**
     * @ORM\OneToMany(targetEntity="Uczen", mappedBy="klasa", cascade={"persist", "remove"})
     */
    private $uczniowie;

    /**
     * @ORM\OneToMany(targetEntity="Przedmiot", mappedBy="klasa", cascade={"persist", "remove"})
     */
    private $przedmioty;

    public function __construct(string $nazwa, int $poziom)
    {
        $this->nazwa = $nazwa;
        $this->poziom = $poziom;
        $this->uczniowie = new ArrayCollection();
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

    public function getNazwa(): ?string
    {
        return $this->nazwa;
    }

    public function setNazwa(string $nazwa): void
    {
        $this->nazwa = $nazwa;
    }

    public function getPoziom(): ?int
    {
        return $this->poziom;
    }

    public function setPoziom(int $poziom): void
    {
        $this->poziom = $poziom;
    }

    public function getNauczyciel(): ?Nauczyciel
    {
        return $this->nauczyciel;
    }

    public function setNauczyciel(Nauczyciel $nauczyciel): void
    {
        $this->nauczyciel = $nauczyciel;
    }

    /**
     * @return Collection|Uczen[]
     */
    public function getUczniowie(): Collection
    {
        return $this->uczniowie;
    }

    public function addUczen(Uczen $uczen): void
    {
        if (!$this->uczniowie->contains($uczen)) {
            $this->uczniowie[] = $uczen;
            $uczen->setKlasa($this);
        }
    }

    public function removeUczen(Uczen $uczen): void
    {
        if ($this->uczniowie->removeElement($uczen)) {
            if ($uczen->getKlasa() === $this) {
                $uczen->setKlasa(null);
            }
        }
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
            $przedmiot->setKlasa($this);
        }
    }

    public function removePrzedmiot(Przedmiot $przedmiot): void
    {
        if ($this->przedmioty->removeElement($przedmiot)) {
            if ($przedmiot->getKlasa() === $this) {
                $przedmiot->setKlasa(null);
            }
        }
    }
}
?>