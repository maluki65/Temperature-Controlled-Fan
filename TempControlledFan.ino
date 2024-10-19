#include <DHT.h>  // DHT sensor library

// Pin definitions
#define FAN_PIN 5           // Pin to control the fan (relay or transistor)
#define LED_PIN 13          // Pin for status LED
#define DHT_PIN 4           // Pin connected to the DHT sensor
#define DHTTYPE DHT11       // Type of DHT sensor (DHT11 or DHT22)

// Threshold for temperature control
const float tempThreshold = 30.0;  // Threshold temperature in °C

// DHT sensor initialization
DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(FAN_PIN, OUTPUT);  // Fan control pin
  pinMode(LED_PIN, OUTPUT);  // Status LED pin
  
  // Start the DHT sensor
  dht.begin();
  
  // Ensure the fan is off initially
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read temperature from the DHT sensor
  float temperature = dht.readTemperature();

  // Check if the sensor reading is valid
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature to Serial monitor for debugging
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Control the fan based on the temperature threshold
  if (temperature >= tempThreshold) {
    // Turn on the fan if the temperature exceeds the threshold
    digitalWrite(FAN_PIN, HIGH);   // Fan ON
    digitalWrite(LED_PIN, HIGH);   // LED ON to indicate fan is running
    Serial.println("Fan is ON");
  } else {
    // Turn off the fan if the temperature is below the threshold
    digitalWrite(FAN_PIN, LOW);    // Fan OFF
    digitalWrite(LED_PIN, LOW);    // LED OFF as fan is not running
    Serial.println("Fan is OFF");
  }

  // Wait for 2 seconds before the next reading
  delay(2000);
}

