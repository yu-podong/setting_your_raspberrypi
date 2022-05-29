<?php
	$os_version = "raspberryPI-light version";
	$user_name = "yu-podong";
?>

<!DOCTYPE html>
<html lang="en">
	<head>
		<meta charset="UTF-8">
		<meta http-equiv="X-UA-Compatible" content="IE=edge">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<title>Sensor Testing</title>
	</head>
	<body>
		<section>
			<!-- Top bar -->
			<header>LOGO</header>
			<div>
				<!-- Left nab-bar -->
				<nav class="nav-bar">
					<!-- Board info -->
					<ul class="board-info">
						<li class="title">Board 정보확인</li>
						<li>
							<span class="var-name">OS version</span>
							<span class="value"><?=$os_version?></span>
						</li>
						<li>
							<span class="var-name">User Name</span>
							<span class="value"><?=$user_name?></span>
						</li>
					</ul>
					<!-- Menu -->
					<ul class="menu">
						<li class="title">Menu</li>
						<li class="item">Sensor</li>
						<li class="item">Actuator</li>
						<li class="item">Connection state</li>
					</ul>
				</nav>
				<!-- Contents -->
				<article>
					<!-- Sensor part -->
					<div class= "left">
						<span class="title">Sensor</span>
						<table class="sensor">
							<tbody>
								<tr>
									<td>조도 센서</td>
									<td>연결</td>
								</tr>
								<tr>
									<td>온도/습도 센서</td>
									<td>미연결</td>
								</tr>
								<tr>
									<td>사운드 센서</td>
									<td>미연결</td>
								</tr>
								<tr>
									<td>초음파 센서</td>
									<td>연결</td>
								</tr>
								<tr>
									<td>불꽃 센서</td>
									<td>미연결</td>
								</tr>
								<tr>
									<td>가스 센서</td>
									<td>연결</td>
								</tr>
								<tr>
									<td>근접 센서</td>
									<td>미연결</td>
								</tr>
							</tbody>
						</table>
					</div>
					<!-- Actuator part -->
					<div class="right">
						<span class="title">Actuator</span>
						<table class="actuator">
							<tbody>
								<tr>
									<td>Water pump</td>
									<td>연결</td>
								</tr>
								<tr>
									<td>Fan control</td>
									<td>미연결</td>
								</tr>
								<tr>
									<td>LED control</td>
									<td>미연결</td>
								</tr>
								<tr>
									<td>Buzzer</td>
									<td>연결</td>
								</tr>
								<tr>
									<td>RGB LED</td>
									<td>미연결</td>
								</tr>
								<tr>
									<td>Servo motor</td>
									<td>연결</td>
								</tr>
							</tbody>
						</table>
					</div>
				</article>
			</div>
		</section>
	</body>
</html>