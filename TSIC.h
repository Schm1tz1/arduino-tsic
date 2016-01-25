/**
* Library for reading TSIC digital temperature sensors like 305 and 206
* using the Arduino platform.
*
* Copyright: Rolf Wagner
* Date: March 9th 2014
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

#ifndef TSIC_h
#define TSIC_h

#include "Arduino.h"

class TSIC {
	public:
		explicit TSIC(uint8_t signal_pin, uint8_t vcc_pin);
		uint8_t getTemperature(uint16_t *temp_value16);
		float calc_Celsius(uint16_t *temperature16);
	private:
    static const int32_t StartTimeout = 60000; 
    static const int16_t BitTimeout = 200;
    static const int16_t MaxStrobe = 80;
		uint8_t m_vcc_pin;
    volatile uint8_t* m_signal_input_reg;
    uint8_t m_signal_mask;
    uint8_t readSens(uint8_t *temp_value);
    uint8_t readSignal() { return (*m_signal_input_reg) & m_signal_mask ? HIGH : LOW; }
    inline void switchOn() { digitalWrite(m_vcc_pin, HIGH); }
    inline void switchOff() { digitalWrite(m_vcc_pin, LOW); }
};

#endif /* TSIC_H */

