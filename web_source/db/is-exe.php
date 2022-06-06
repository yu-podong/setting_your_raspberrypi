<?php 
include_once "lib.php";

$db = new db();

$userID = $_GET['id'];
$db->get("SELECT * FROM execute WHERE userid=$userID", $rs, $rn);

echo $rs[0]['exenum'];

?>
