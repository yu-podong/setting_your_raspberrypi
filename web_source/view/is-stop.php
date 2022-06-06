<?php
$conn = mysqli_connect("localhost", "root", "team02", "syr");

$userid=$_GET['userid'];
$rs = mysqli_query($conn, "select * from stop where userid = {$userid};");
$rn = mysqli_num_rows($rs);

while($row = mysqli_fetch_array($rs)){
  echo $row[0]." ";
  echo $row[1]." ";
}

mysqli_close($conn);

?>
