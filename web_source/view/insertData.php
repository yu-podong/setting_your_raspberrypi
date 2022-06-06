<?php
$conn = mysqli_connect("localhost", "root", "1234", "syr");

$value=$_GET['value'];
$select=$_GET['select'];
$userid=$_GET['userid'];

//excute 테일블에 업데이트
mysqli_query($conn, "UPDATE execute SET exenum = {$select} WHERE userid = {$userid};");

// echo $select;
// echo $value;
// echo $userid;
if($select == 1){ //조도 센서
  mysqli_query($conn, "UPDATE sensor SET sensor1 = {$value} WHERE userid = {$userid};");

}
else if($select == 2){ //온습도 센서
  mysqli_query($conn, "UPDATE sensor SET sensor2 = {$value} WHERE userid = {$userid};");
  
}
else if($select == 3){ //사운드 센서
  mysqli_query($conn, "UPDATE sensor SET sensor3 = {$value} WHERE userid = {$userid};");

}
else if($select == 4){ //초음파 센서
  mysqli_query($conn, "UPDATE sensor SET sensor4 = {$value} WHERE userid = {$userid};");

}
else if($select == 5){ //불꽃 센서
  mysqli_query($conn, "UPDATE sensor SET sensor5 = {$value} WHERE userid = {$userid};");

}
else if($select == 6){ //가스 센서
  mysqli_query($conn, "UPDATE sensor SET sensor6 = {$value} WHERE userid = {$userid};");

}
else if($select == 7){ //근접 센서
  mysqli_query($conn, "UPDATE sensor SET sensor7 = {$value} WHERE userid = {$userid};");

}
else if($select == 8){ //워터펌프
  mysqli_query($conn, "UPDATE actuator SET actuator1 = {$value} WHERE userid = {$userid};");
  
}
else if($select == 9){ //팬
  mysqli_query($conn, "UPDATE actuator SET actuator2 = {$value} WHERE userid = {$userid};");

}
else if($select == 10){//LED

  mysqli_query($conn, "UPDATE actuator SET actuator3 = {$value} WHERE userid = {$userid};");
}
else if($select == 11){//부저

  mysqli_query($conn, "UPDATE actuator SET actuator4 = {$value} WHERE userid = {$userid};");
}
else if($select == 12){//RGB LED

  mysqli_query($conn, "UPDATE actuator SET actuator5 = {$value} WHERE userid = {$userid};");
}
else if($select == 13){ //모터
  mysqli_query($conn, "UPDATE actuator SET actuator6 = {$value} WHERE userid = {$userid};");

}

mysqli_close($conn);

?>
