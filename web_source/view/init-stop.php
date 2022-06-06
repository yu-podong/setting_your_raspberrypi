<?php
$conn = mysqli_connect("localhost", "root", "1234", "syr");

$userid=$_GET['userid'];
$rs = mysqli_query($conn, "UPDATE stop SET isstop = 0 WHERE userid = {$userid};");
$rs = mysqli_query($conn, "UPDATE execute SET exenum = 0 WHERE userid = {$userid};");
$rn = mysqli_num_rows($rs);

mysqli_close($conn);

?>
