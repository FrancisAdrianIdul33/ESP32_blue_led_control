<?php
$conn = new mysqli("localhost", "root", "", "esp32_control");

if ($conn->connect_error) {
    die("0"); // Return 0 on DB failure
}

$result = $conn->query("SELECT status FROM led_control WHERE id = 1");
$row = $result->fetch_assoc();

echo $row['status']; // Returns "1" or "0"
$conn->close();
?>