<?php
include_once "lib.php";

$db = new db();

$userID = $_GET['id'];

$db->act("UPDATE stop SET isstop=0 WHERE userid=$userID");
$db->act("UPDATE execute SET exenum=0 WHERE userid=$userID");

$db->finish();
?>
