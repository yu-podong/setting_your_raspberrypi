<?php
include_once "../db/lib.php";

$db = new db();

$userID = $_GET['id'];
$sensor1;
$sensor2;
$act1;
$act2;

$db->get("SELECT * FROM	sensor WHERE userid=$userID", $rs1, $rn1);
$db->get("SELECT * FROM actuator WHERE userid=$userID", $rs2, $rn2);

$db->finish();

// 디바이스 연결상태 가시화
// sensor

for($i = 1; $i < 8; $i++) {
	if($rs1[0]['sensor'.(string)$i] == -1) {
		$sensor2[$i] = '테스트 필요';
		$sensor1[$i] = '';
	}	
	else if($rs1[0]['sensor'.(string)$i] == 1) {
		$sensor2[$i] = '연결';
		$sensor1[$i] = 'connect';
	}	
	else if($rs1[0]['sensor'.(string)$i] == 0) {
		$sensor2[$i] = '미연결';
		$sensor1[$i] = 'non-connect';
	}
}

for($i = 1; $i < 7; $i++) {
	if($rs2[0]['actuator'.(string)$i] == -1) {
		$act2[$i] = '테스트 필요';
		$act1[$i] = '';
	}	
	else if($rs2[0]['actuator'.(string)$i] == 1) {
		$act2[$i] = '연결';
		$act1[$i] = 'connect';

	}	
	else if($rs2[0]['actuator'.(string)$i] == 0) {
		$act2[$i] = '미연결';
		$act1[$i] = 'non-connect';

	}
}
?>

<!DOCTYPE html>
<html lang="en">
	<head>
		<meta charset="UTF-8">
		<meta http-equiv="X-UA-Compatible" content="IE=edge">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">

		<!-- Nanum Gothic font -->
		<link rel="preconnect" href="https://fonts.googleapis.com">
		<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
		<link href="https://fonts.googleapis.com/css2?family=Nanum+Gothic:wght@400;700;800&display=swap" rel="stylesheet">

		<!-- font awesome -->
		<script src="https://kit.fontawesome.com/8196d5cfd4.js" crossorigin="anonymous"></script>

		<!-- css file -->
		<link rel="stylesheet" href="../style/common.css">
		<link rel="stylesheet" href="../style/state.css">

		<title>Connection Check</title>
	</head>
	<body>
		<section class="connection">
			<!-- Top bar -->
			<header>Setting-your-Raspberry-Pi</header>
			<div>
				<!-- Left nab-bar -->
				<nav class="nav-bar">
					<ul class="menu">
						<li class="title">Menu</li>
						<li class="item"><a href="./sensor-test.php?id=<?php echo $userID?>">Sensor</a></li>
						<li class="item"><a href="./actuator-test.php?id=<?php echo $userID?>">Actuator</a></li>
						<li class="item click"><a href="./state.php?id=<?php echo $userID?>">Connection check</a></li>
					</ul>

					<div class="help">
						<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 320 512">
							<!--! Font Awesome Pro 6.1.1 by @fontawesome - https://fontawesome.com License - https://fontawesome.com/license (Commercial License) Copyright 2022 Fonticons, Inc. -->
							<path d="M204.3 32.01H96c-52.94 0-96 43.06-96 96c0 17.67 14.31 31.1 32 31.1s32-14.32 32-31.1c0-17.64 14.34-32 32-32h108.3C232.8 96.01 256 119.2 256 147.8c0 19.72-10.97 37.47-30.5 47.33L127.8 252.4C117.1 258.2 112 268.7 112 280v40c0 17.67 14.31 31.99 32 31.99s32-14.32 32-31.99V298.3L256 251.3c39.47-19.75 64-59.42 64-103.5C320 83.95 268.1 32.01 204.3 32.01zM144 400c-22.09 0-40 17.91-40 40s17.91 39.1 40 39.1s40-17.9 40-39.1S166.1 400 144 400z"/>
						</svg>
					</div>
				</nav>
				<!-- Contents -->
				<article>
					<div class="contents">
						<div class="left">
							<span class="page-title">Sensor</span>
							<ul class="list">
								<li>
									<span class="device-name">조도 센서</span>
									<span class="<?php echo $sensor1[1]?>"><?php echo $sensor2[1]?></span>
								</li>
								<li>
									<span class="device-name">온도/습도 센서</span>
									<span class="<?php echo $sensor1[2]?>"><?php echo $sensor2[2]?></span>
								</li>
								<li>
									<span class="device-name">사운드 센서</span>
									<span class="<?php echo $sensor1[3]?>"><?php echo $sensor2[3]?></span>
								</li>
								<li>
									<span class="device-name">초음파 센서</span>
									<span class="<?php echo $sensor1[4]?>"><?php echo $sensor2[4]?></span>
								</li>
								<li>
									<span class="device-name">불꽃 센서</span>
									<span class="<?php echo $sensor1[5]?>"><?php echo $sensor2[5]?></span>
								</li>
								<li>
									<span class="device-name">가스 센서</span>
									<span class="<?php echo $sensor1[6]?>"><?php echo $sensor2[6]?></span>
								</li>
								<li>
									<span class="device-name">근접 센서</span>
									<span class="<?php echo $sensor1[7]?>"><?php echo $sensor2[7]?></span>
								</li>
							</ul>
						</div>
						<div class="right">
							<span class="page-title">Actuator</span>
							<ul class="list">
								<li>
									<span class="device-name">Water pump</span>
									<span class="<?php echo $act1[1]?>"><?php echo $act2[1]?></span>
								</li>
								<li>
									<span class="device-name">Fan control</span>
									<span class="<?php echo $act1[2]?>"><?php echo $act2[2]?></span>
								</li>
								<li>
									<span class="device-name">LED control</span>
									<span class="<?php echo $act1[3]?>"><?php echo $act2[3]?></span>
								</li>
								<li>
									<span class="device-name">Buzzer</span>
									<span class="<?php echo $act1[4]?>"><?php echo $act2[4]?></span>
								</li>
								<li>
									<span class="device-name">RGB LED</span>
									<span class="<?php echo $act1[5]?>"><?php echo $act2[5]?></span>
								</li>
								<li>
									<span class="device-name">Servo motor</span>
									<span class="<?php echo $act1[6]?>"><?php echo $act2[6]?></span>
								</li>
							</ul>
						</div>
					</div>
				</article>
			</div>
		</section>
	</body>
</html>
