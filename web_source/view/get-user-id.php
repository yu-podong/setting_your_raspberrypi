<?php
$conn = mysqli_connect("localhost", "root", "1234", "syr");

$userName=$_GET['userName'];
$userStuID=$_GET['userStuID'];
$userID=$_GET['userID'];

$rs = mysqli_query($conn, "select * from user where stunum = '{$userStuID}' ");
$rn = mysqli_num_rows($rs);
// echo $rn; 

// echo $rs[0];
// echo $rs[1];

// for ($i=0; $i<$rn; $i++) {
// echo $rs[$i][0] ." ". $rs[$i][1] ."<br>\n";
// }

while($row = mysqli_fetch_array($rs)){
  echo $row[0]." ";
  echo $row[1]." ";
  echo $row[2]."";
}

mysqli_close($conn);

?>
