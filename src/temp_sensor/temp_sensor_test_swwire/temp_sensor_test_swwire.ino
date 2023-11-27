#include <Wire.h>
#include <SoftwareWire.h>

// TMP100 I2C address
#define TMP100_ADDR 0x48

// Custom I2C pins
#define CUSTOM_SDA_PIN 10  // Change this to the actual pin you are using for SDA
#define CUSTOM_SCL_PIN 11  // Change this to the actual pin you are using for SCL

SoftwareWire myWire(CUSTOM_SDA_PIN, CUSTOM_SCL_PIN);

void setup() {
  Serial.begin(9600);
  myWire.begin();
}

void loop() {
  float temperature = readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000); // Delay for one second
}

float readTemperature() {
  myWire.beginTransmission(TMP100_ADDR);
  myWire.write(0); // Start reading from the temperature register
  myWire.endTransmission();

  myWire.requestFrom(TMP100_ADDR, 2); // Request 2 bytes of data

  if (myWire.available() >= 2) {
    int16_t rawTemperature = myWire.read() << 8 | myWire.read();
    float temperature = rawTemperature * 0.0625; // Each bit represents 0.0625 degrees Celsius
    return temperature;
  } else {
    Serial.println("Error: Unable to read temperature from TMP100.");
    return -1.0; // Error indicator
  }
}
