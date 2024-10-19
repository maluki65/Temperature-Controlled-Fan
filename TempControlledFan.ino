#include <DHT.h> 

// Pin definitions
#define FAN_PIN 5           // Pin to control the fan
#define LED_PIN 13          // Pin for status LED
#define DHT_PIN 4           // Pin connected to the DHT sensor
#define DHTTYPE DHT11       // Type of DHT sensor

const float tempThreshold = 30.0;  // Threshold temperature in °C

// DHT sensor initialization
DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  // On initializing serial communication
  Serial.begin(9600);
  
  // On nitializing pins
  pinMode(FAN_PIN, OUTPUT);  // Fan control pin
  pinMode(LED_PIN, OUTPUT);  // Status LED pin
  
  // On starting the DHT sensor
  dht.begin();
  

  digitalWrite(FAN_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read temperature from the DHT sensor
  float temperature = dht.readTemperature();

  // On checking if the sensor reading is valid
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature to Serial monitor for debugging
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");


  if (temperature >= tempThreshold) {
    // On turning on the fan if the temperature exceeds the threshold
    digitalWrite(FAN_PIN, HIGH);   
    digitalWrite(LED_PIN, HIGH);   
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

