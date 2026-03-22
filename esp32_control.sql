CREATE DATABASE esp32_control;

USE esp32_control;

CREATE TABLE led_control (
  id INT PRIMARY KEY DEFAULT 1,
  status TINYINT(1) NOT NULL DEFAULT 0
);

-- Insert the initial row (only ever 1 row)
INSERT INTO led_control (id, status) VALUES (1, 0);