<?php
class db {
	var $conn;

	function db() {
		$this->conn = mysqli_connect("localhost", "root", "team02", "syr") or die (mysqli_connect_error());
	}

	function finish() {
		mysqli_close($this->conn) or die (mysqli_error($this->conn));
	}

	function act($q) {
		mysqli_query($this->conn, $q) or die (mysqli_error($this->conn));
	}

	function get($q, &$rs, &$rn) {
		$rs=NULL;
		$rn=0;
		$rs1 = mysqli_query($this->conn, $q) or die (mysqli_error($this->conn));
		$rn = mysqli_num_rows($rs1);
		
		while ($row=mysqli_fetch_array($rs1))
			$rs[] = $row;
	}
}
?>
