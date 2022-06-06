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
		<link rel="stylesheet" href="../style/test.css">

		<!-- js file -->
		<script src="../js/sensor.js" defer></script>
		<script src="../js/sensor-btn.js" defer></script>

		<title>Sensor Testing</title>
	</head>
	<body>
		<section class="testing">
			<!-- Top bar -->
			<header>Setting-your-Raspberry-Pi</header>
			<div>
				<!-- Left nab-bar -->
				<nav class="nav-bar">
					<ul class="menu">
						<li class="title">Menu</li>
						<li class="item click"><a href="./sensor-test.html">Sensor</a></li>
						<li class="item"><a href="./actuator-test.html">Actuator</a></li>
						<li class="item"><a href="./state.html">Connection check</a></li>
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
								<li class="item1 click">조도 센서</li>
								<li class="item2">온도/습도 센서</li>
								<li class="item3">사운드 센서</li>
								<li class="item4">초음파 센서</li>
								<li class="item5">불꽃 센서</li>
								<li class="item6">가스 센서</li>
								<li class="item7">근접 센서</li>
							</ul>
						</div>
						<div class="right">
							<ul class="connect-method">
								<li class="title">⚙ 연결방법</li>
								<li class="image"><img src="../resource/image/sensor/light.png" alt=""></li>
								<li><button class="check-btn">연결상태 확인</button></li>
							</ul>
							<ul class="result">
								<li class="title">✔ 추가 기능</li>
								<li><button class="stop-btn">stop testing</button></li>
								<li><button class="view-btn" onclick="loadText()">view code</button></li>
								<li><button class="download-btn" onclick="downloadFile()">download code</button></li>
							</ul>
						</div>
					</div>
				</article>
			</div>
		</section>
		<div class="view-code hidden">
			<span class="output"></span>
		</div>
	</body>
</html>