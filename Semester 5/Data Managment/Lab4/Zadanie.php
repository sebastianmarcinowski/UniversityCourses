<?php
    require_once __DIR__ . '/../vendor/autoload.php';
    use Doctrine\DBAL\DriverManager;
    $params = [
        'dbname' => 'labs',
        'user' => 'root',
        'password' => '',
        'host' => 'localhost',
        'driver' => 'pdo_mysql'
    ];

    $conn = DriverManager::getConnection($params);

    //Zadanie 4 podpunkt 1
    /*
    $querybuilder = $conn->createQueryBuilder();
    $querybuilder->select('customerName', 'creditLimit')
        ->from('customers')
        ->where('country = :country')
        ->setParameter('country', 'USA')
        ->orderBy('creditLimit', 'DESC');
    $res = $querybuilder->executeQuery();
    while($row = $res->fetchAssociative()){
        echo $row['customerName'] . " " . $row['creditLimit'] . "\n";
    }
    */

    /*
    $querybuilder_2 = $conn->createQueryBuilder();
    $querybuilder_2->select('c.customerName','c.customerNumber', 'e.lastName', 'e.firstName')
    ->from('customers', 'c')
    ->join('c','employees', 'e', 'c.salesRepEmployeeNumber = e.employeeNumber');
    $res2 = $querybuilder_2->executeQuery();
    while($row = $res2->fetchAssociative()){
        echo $row['customerName'] . " " . $row['customerNumber'] . " " . $row['lastName'] . " " . $row['firstName'] . "\n";
    }
    */

    $sm = new \Doctrine\DBAL\Schema\Schema();

    $tab = $sm->createTable('tabLab4');
    $tab->addColumn('id', 'integer', ['autoincrement' => true]);
    $tab->addColumn('napis', 'text', ['notnull' => true]);
    $tab->addColumn('liczba', 'integer', ['notnull' => true]);
    $tab->setPrimaryKey(['id']);

    $sql = $sm->toSql($conn->getDatabasePlatform());
    $conn->executeStatement($sql[0]);
    $napisy = ['napis1','napis2','napis3','napis4','napis5','napis6','napis7','napis8','napis9','napis10'];
    $querybuilder_3 = $conn->createQueryBuilder();
    for ($i = 0; $i < 10; $i++) {
        $querybuilder_3->insert('tabLab4')
            ->setValue('napis','?')
            ->setValue('liczba','?')
            ->setParameters([$napisy[$i],$i]);
        $querybuilder_3->executeStatement();
    }

?>