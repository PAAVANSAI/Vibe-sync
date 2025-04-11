// Libraries for ESP8266 WiFi and Firebase
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Define WiFi credentials
#define wifi_name "chinna"
#define wifi_password "chinna123"

// Define Firebase credentials
#define firebase_url "https://home-c00e6-default-rtdb.firebaseio.com/"
#define firebase_secretkey "XAZcHm12lnOTCny3UkSIo4f1T67E1BmYBACekASW"

// Pin for the IR sensor and LED
#define IR_SENSOR_PIN 4  // Define IR sensor pin
#define LED_PIN 2        // Define LED pin

// Create FirebaseData object
FirebaseData firebasedata;

// Setup WiFi and Firebase
void setup() {
  Serial.begin(115200);

  // Pin configurations
  pinMode(LED_PIN, OUTPUT);
  pinMode(IR_SENSOR_PIN, INPUT);

  // Connect to WiFi
  WiFi.begin(wifi_name, wifi_password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Initialize Firebase
  Firebase.begin(firebase_url, firebase_secretkey);
}

// Main loop
void loop() {
  // Read the state of the IR sensor
  int sensorState = digitalRead(IR_SENSOR_PIN);  // 1 if detected, 0 if not

  // Send data to Firebase based on the sensor state
  if (sensorState == LOW) {
    // If sensor detects something, send 1 to Firebase
    if (Firebase.setInt(firebasedata, "/sensor/state", 1)) {
      Serial.println("Sensor detected: 1 sent to Firebase");
      digitalWrite(LED_PIN, HIGH); // Turn on LED if detected
    }
  } else {
    // If no detection, send 0 to Firebase
    if (Firebase.setInt(firebasedata, "/sensor/state", 0)) {
      Serial.println("No detection: 0 sent to Firebase");
      digitalWrite(LED_PIN, LOW);  // Turn off LED if not detected
    }
  }

  delay(1000); // Wait 1 second before checking again
}
