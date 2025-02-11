<?php
    try{
        $conn1 = new PDO("mysql:host=localhost;dbname=labs", "root", "");
        $conn1->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $tabela = $conn1->exec("CREATE TABLE IF NOT EXISTS lab2 (id int NOT NULL PRIMARY KEY AUTO_INCREMENT, napis text NOT NULL, liczba int NOT NULL)");
        $usun = $conn1->exec("DELETE FROM lab2");
        $records = array(1 => 'January','February','March','April','May','June','July',NULL, 'August','September','October','November','December');
        $addstmt = $conn1->prepare('insert into lab2 (napis,liczba) values(?,?)');
        $conn1->beginTransaction();
        for($i=1;$i<count($records)+1;$i++){
            $addstmt->execute(array($records[$i],rand()));
        }
        $conn1->commit();
        $stmt = $conn1->query('SELECT * FROM lab2');
        while($row = $stmt->fetch()){
            echo $row['napis'] . ' - ' . $row['liczba'] . "\n";
        }
    }
    catch(PDOException $e){
        print $e->getMessage();
        die();
    }
?>