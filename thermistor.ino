#include <math.h>  // Needed for log() function

// Constants for B-parameter equation
const float T0 = 298.15;  // Reference temperature (25C in K)
const float R0 = 10000;   // Resistance at reference temperature (10k ohms)
const float B = 3453;     // B parameter

// Function to read temperature from a thermistor connected to the specified analog input pin
float readThermistor(int pin) {
  int reading = analogRead(pin);  // Read the voltage across the thermistor

  // Check for invalid ADC readings
  if (reading <= 0 || reading >= 1023) {
    Serial.println("Error: Invalid ADC reading");
    return NAN;  // Return not-a-number on error
  }

  float voltage = reading * (5.0 / 1023.0);  // Convert ADC reading to voltage
  float R = 10000 * ((5.0 / voltage) - 1);  // Calculate the thermistor resistance
  float T = 1 / (1/T0 + 1/B * log(R/R0));   // Calculate the temperature using the B-parameter equation

  T = T - 273.15;  // Convert from Kelvin to Celsius

  // Check for unreasonable temperatures
  if (T < -40 || T > 125) {
    Serial.println("Error: Unreasonable temperature value");
    return NAN;  // Return not-a-number on error
  }

  return T;  // Return the calculated temperature
}

void setup() {
  Serial.begin(9600);  // Start the serial communication with the computer
}

void loop() {
  float temperature = readThermistor(A0);  // Read the temperature from the thermistor

  // Check for errors
  if (isnan(temperature)) {
    Serial.println("Error reading temperature");
  } else {
    Serial.println(temperature);  // Print the temperature to the serial monitor
  }

  delay(1000);  // Wait for 1 second before the next reading
}
