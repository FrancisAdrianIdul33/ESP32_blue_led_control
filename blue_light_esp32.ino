#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "shinakira";
const char* password = "12312309";
const char* serverURL = "http://192.168.118.115/led_control/led_status.php";

void blinkBeforeAction(int finalState) {
  // Blink for 5 seconds (10 blinks)
  for (int i = 0; i < 10; i++) {
    digitalWrite(2, HIGH);
    delay(250);
    digitalWrite(2, LOW);
    delay(250);
  }
  // Then set the final state
  digitalWrite(2, finalState);
}

int lastStatus = -1;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);

    int httpCode = http.GET();

    if (httpCode == 200) {
      String payload = http.getString();
      payload.trim();
      int newStatus = payload.toInt();

      // Only trigger blink when status CHANGES
      if (newStatus != lastStatus) {
        Serial.println("Status changed → blinking...");
        blinkBeforeAction(newStatus);
        lastStatus = newStatus;
      }
    }

    http.end();
  }

  delay(2000);
}