<?php

namespace App\Entity;
use Doctrine\ORM\Mapping as ORM;
/**
 * @ORM\Entity
 */
class Przedmiot
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
     * @ORM\ManyToOne(targetEntity="Nauczyciel", cascade={"persist", "remove"})
     * @ORM\JoinColumn(name="nauczyciel_id", referencedColumnName="id")
     */
    private $nauczyciel;

    /**
     * @ORM\ManyToOne(targetEntity="Klasa", cascade={"persist", "remove"})
     * @ORM\JoinColumn(name="klasa_id", referencedColumnName="id")
     */
    private $klasa;

    public function __construct(string $nazwa = null)
    {
        $this->nazwa = $nazwa;
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

    public function getNauczyciel(): ?Nauczyciel
    {
        return $this->nauczyciel;
    }

    public function setNauczyciel(Nauczyciel $nauczyciel): void
    {
        $this->nauczyciel = $nauczyciel;
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