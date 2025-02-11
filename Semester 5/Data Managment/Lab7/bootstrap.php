<?php
    require_once __DIR__ . '/vendor/autoload.php';
    use Doctrine\ORM\ORMSetup;
    use Doctrine\ORM\Tools\Setup;
    use Doctrine\ORM\EntityManager;
    use Doctrine\ORM\ORMException;

    $config = Setup::createAnnotationMetadataConfiguration(array(__DIR__."/src"),true, null, null, false);
    $conn = array(
       'dbname' => 'labs',
        'user' => 'root',
        'password' => '',
        'host' => 'localhost',
        'driver' => 'pdo_mysql',
        'charset' => 'utf8');

    try {
        $em = EntityManager::create($conn, $config);
        echo "EntityManager został utworzony pomyślnie!";
    } catch (\Doctrine\ORM\ORMException $e) {
        echo "Błąd: " . $e->getMessage();
        exit(1);
    }
?>