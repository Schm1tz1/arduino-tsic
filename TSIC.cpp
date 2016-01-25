/**
* Library for reading TSIC digital temperature sensors like 305 and 206
* using the Arduino platform.
*
* Copyright: Rolf Wagner
* Date: March 9th 2014
* 
* Version 2.2 (changes by STefan Gmeiner, 2016-01-25)
*     - integrate parity check during sensor reading
*     - replace loop counting by delay measuring to ensure consistent
*       behaviour between loops and when interrupts delay the loop
*       unexpectly
*     - simplify celsius calculation
*     - replace pre-processor functions by inline functions to reduce name conflicts
*     - pre compute the data port and mask for faster pin access (instead of
*       digitalRead)
*     - now only 210 bytes for dynamic memory is used
*     
* Version 2.1 (changes by Matthias Eibl, 2015-03-31)
* 		- if the TSIC returns an error, the Power PIN is 
* 		  turned LOW (otherwise it produces errors as the 
* 		  start for a healthy sensor is not defined properly.)
* 		- the timeouts are optimized for a faster identification of 
* 		  not connected sensors (if no sensor is connected, the 
* 		  Data Pin will remain in state LOW. As the strobe is usually
* 		  ~ 60us, it is sufficient to set the timeout to a value of
* 		  <<100 loops in the second while loop "while (TSIC_LOW){..."
* 		  in the function "TSIC::readSens". One cycle is -depending on
* 		  the CPU frequency used- ~10us.)
* 
* 
* 
* 
* Version 2
*		Improvements:
*		- Arduino > 1.0 compatible
*		- corrected offset (about +2°C)
*		- code run time optimization
*		- no freezing of system in case sensor gets unplugged
*		- measure strobetime instead of constant waiting time (-> high temperature stable)
*		- code cleanup
*		- space optimization, now only 239 byte
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* http://playground.arduino.cc/Code/Tsic
*/

#include "Arduino.h"
#include "TSIC.h"

// Initialize inputs/outputs
TSIC::TSIC(uint8_t signal_pin, uint8_t vcc_pin)
	: m_vcc_pin(vcc_pin) 
{
    pinMode(m_vcc_pin, OUTPUT);
    pinMode(signal_pin, INPUT);
    m_signal_input_reg = portInputRegister(digitalPinToPort(signal_pin));
    m_signal_mask = digitalPinToBitMask(signal_pin);
}

// read temperature
uint8_t TSIC::getTemperature(uint16_t *temp_value16){
		switchOn();
		delayMicroseconds(50);     // wait for stabilization
    uint8_t ok = readSens(((uint8_t*)temp_value16)+1);
    ok = ok && readSens(((uint8_t*)temp_value16)+0);
    switchOff();
    return ok;
}

//-------------Unterprogramme-----------------------------------------------------------------------

/*	Temperature conversion from uint to float in °C.
*/
float TSIC::calc_Celsius(uint16_t *temperature16){
  return (*temperature16 * 200.0) / 2047.0 - 50.0;
}

uint8_t TSIC::readSens(uint8_t *temp_value){
  int32_t start;
  int16_t strobe;
  uint8_t parity = 0;
  uint16_t data = 0;

  // wait for strobe start (falling edge)
  start = micros();
  while (readSignal())
  {
    // 32-bit to support longer timeouts on start bit
    if (((int32_t)micros()) - start > StartTimeout) return 0;
  }

  // measure strobe length (raising edge)
  start = micros();
  while (!readSignal())
  {
    // 16-bit -> max. timeout 32000us
    if (((int16_t)micros()) - ((int16_t)start) > BitTimeout) return 0;
  }
  strobe = micros() - start;
  // strobe is nominal about 62.5us
  if (strobe > MaxStrobe) return 0;
  
  for (uint8_t i=0; i<9; i++) {
    
    // Wait for bit start
    start = micros();
    while (readSignal()) { // wait for falling edge
      // 16-bit -> max. timeout 32000us
      if (((int16_t)micros()) - ((int16_t)start) > BitTimeout) return 0;
    }
    
    // Delay strobe length
    start = micros();
    while (((int16_t)micros()) - ((int16_t)start) < strobe) {
    }
    data <<= 1;
    if (readSignal()) {
      data |= 1;
      parity++;
    }
    
    // Wait for bit end
    start = micros();
    while (!readSignal()) {   // wait for rising edge
      if (((int16_t)micros()) - ((int16_t)start) > BitTimeout) return 0;
    }
  }

  // remove parity
  data >>= 1;
  *temp_value = data;
  
  return (parity % 2) ? 0 : 1;
}


