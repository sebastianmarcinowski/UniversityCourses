<?php
    $mysqli = new mysqli("localhost", "root","", "labs");
    $res = mysqli_query($mysqli, "SELECT * FROM tabela");
    while($row = mysqli_fetch_array($res)){
        echo $row['napis'] . "\n";
    }
?>