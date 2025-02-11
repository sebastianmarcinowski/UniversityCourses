<?php
    $db=new mysqli("localhost", "root","", "labs");
    $db->query("create table if not exists tabela2 (liczba int, napis text)");
    $db->query("insert into tabela2 values (123,'abc')");

    $res = $db->query("select * from tabela2");

    while($row = $res->fetch_array()){
        echo $row['napis'] . "\n";
    }

?>