<?php
include_once "lib.php";

$db = new db();

$userName = $_POST['name'];
$stuNum = $_POST['stunum'];
$userID;

// DB에 저장되어 있는 사용자인지 확인
$db->get("select * from user where stunum='$stuNum'", $rs, $rn);

// 신규 사용자면
if($rn == 0) {
        // user에 정보 삽입
        $db->act("INSERT INTO user(name, stunum) VALUES('$userName', '$stuNum')");

        // 해당 사용자의 ID 확인
        $db->get("select * from user where stunum='$stuNum'", $rs, $rn);
        // 사용자의 ID 저장
        $userID = $rs[0]['id'];

        // 초기 세팅 진행
        $db->act("INSERT INTO execute VALUES($userID, 0)");
        $db->act("INSERT INTO stop VALUES($userID, 0)");
        $db->act("INSERT INTO sensor VALUES($userID, -1,-1,-1,-1,-1,-1,-1)");
        $db->act("INSERT INTO actuator VALUES($userID, -1,-1,-1,-1,-1,-1,-1)");
}
// 기존 사용자면
else {
        // 사용자의 ID 저장
        $userID = $rs[0]['id'];
}

$db->finish();

echo $userID;
?>
