<?php
include_once "lib.php";

$db = new db();

$userID = $_POST['id'];
$exeNum = $_POST['exenum'];

echo $userID;

$db->act("UPDATE execute SET exenum=$exeNum WHERE userid=$userID");

$db->finish();
?>
