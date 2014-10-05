/**
 *  test ard-tsiclib by reading the temperature every second
 *  and output the measured data to the serial port
 */

#include "TSIC.h"       // include the library

// instantiate the library, representing the sensor
TSIC Sensor1(4, 2);    // Signalpin, VCCpin
//TSIC Sensor2(5, 2);  // Signalpin, VCCpin, NOTE: we can use the same VCCpin to power both sensors

uint16_t temperature = 0;
float Temperatur_C = 0;

void setup() {
    Serial.begin(9600); // set up the serial port
}

void loop() {
  
  if (Sensor1.getTemperture(&temperature)) {
    Serial.print("uint_16: ");
    Serial.println(temperature);
    Temperatur_C = Sensor1.calc_Celsius(&temperature);
    Serial.print("Temperature: ");
    Serial.print(Temperatur_C);
    Serial.println(" °C");
  }
  
  delay(1000);    // wait 1 seconds
}
