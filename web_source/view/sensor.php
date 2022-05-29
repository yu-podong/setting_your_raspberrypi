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
					<span class="page-title">Sensor</span>
					<div class="contents">
						<div class= "left">
							<ul class="sensor-list">
								<li>조도 센서</li>
								<li>온도/습도 센서</li>
								<li>사운드 센서</li>
								<li>초음파 센서</li>
								<li>불꽃 센서</li>
								<li>가스 센서</li>
								<li>근접 센서</li>
							</ul>
							<ul class="btn-list">
								<li><button class="view-btn">view code</button></li>
								<li><button class="view-btn">download code</button></li>
							</ul>
						</div>
						<div class="right">
							<ul class="connect-method">
								<li class="title">⚙ 연결방법</li>
								<li>Image section</li>
								<li><button class="check-btn">연결상태 확인</button></li>
							</ul>
							<ul class="result">
								<li class="title">✔ 테스트 결과</li>
								<li class="print-code">test result code</li>
							</ul>
						</div>
					</div>
				</article>
			</div>
		</section>
	</body>
</html>