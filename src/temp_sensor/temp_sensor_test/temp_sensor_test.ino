#include <Wire.h>

// TMP100 I2C address
#define TMP100_ADDR 0x48 //Check address!

void setup() {
  Serial.begin(9600); //Check baudrate.
  Wire.begin(); //Default SDA and SCL pins PA_6 PA_7. Must change schematic or find another way.
}

void loop() {
  float temperature = readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000); // Delay for one second
}

float readTemperature() {
  Wire.beginTransmission(TMP100_ADDR);
  Wire.write(0); // Start reading from the temperature register
  Wire.endTransmission();

  Wire.requestFrom(TMP100_ADDR, 2); // Request 2 bytes of data

  if (Wire.available() >= 2) {
    int16_t rawTemperature = Wire.read() << 8 | Wire.read();
    float temperature = rawTemperature * 0.0625; // Each bit represents 0.0625 degrees Celsius
    return temperature;
  } else {
    Serial.println("Error: Unable to read temperature from TMP100.");
    return -1.0; // Error indicator
  }
}

