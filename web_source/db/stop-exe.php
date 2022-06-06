<?php
include_once "lib.php";

$db = new db();

$userID = $_POST['id'];

$db->act("UPDATE stop SET isstop=1 WHERE userid=$userID");

$db->finish();
?>
