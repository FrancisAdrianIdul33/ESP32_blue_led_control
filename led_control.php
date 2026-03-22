<?php
$conn = new mysqli("localhost", "root", "", "esp32_control");

if ($conn->connect_error) {
    die(json_encode(["error" => "DB connection failed"]));
}

header("Content-Type: application/json");

// Handle POST to update status
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $status = intval($_POST['status']);
    $conn->query("UPDATE led_control SET status = $status WHERE id = 1");
    echo json_encode(["status" => $status]);
}

// Handle GET to read status
if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $result = $conn->query("SELECT status FROM led_control WHERE id = 1");
    $row = $result->fetch_assoc();
    echo json_encode(["status" => intval($row['status'])]);
}

$conn->close();
?>