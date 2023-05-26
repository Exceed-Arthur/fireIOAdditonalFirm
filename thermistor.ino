// Constants for thermistor calculations
const int adcPin = PA2;              // ADC pin connected to thermistor
const int referenceVoltage = 5.0;   // Reference voltage of ADC (in volts)
const int adcResolution = 1023;     // ADC resolution (10-bit)

// Thermistor resistance-temperature curve
const float R25 = 330000;   // Resistance at 25°C (in ohms)
const float T1 = 25;        // Reference temperature (in degrees Celsius)
const float B25_85 = 4750;  // B constant (Beta value) from 25°C to 85°C (in K)

void setup() {
  Serial.begin(9600);   // Initialize Serial Monitor
}

void loop() {
  // Read the ADC value
  int adcValue = analogRead(adcPin);

  // Convert ADC value to voltage
  float voltage = (adcValue * referenceVoltage) / adcResolution;

  // Convert voltage to thermistor resistance
  float thermistorResistance = (voltage * R25) / (referenceVoltage - voltage);

  // Convert thermistor resistance to temperature using the Steinhart-Hart equation
  float invTemperature = log(thermistorResistance / R25);
  invTemperature /= B25_85;
  invTemperature += 1.0 / (T1 + 273.15);
  float temperature = 1.0 / invTemperature - 273.15;  // Temperature in Celsius

  // Print the temperature
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000);   // Wait for 1 second before the next reading
}
