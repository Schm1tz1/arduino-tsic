[arduino-tsic][1]
============
This project is a library for TSIC digital temperature sensors (type 206/306/506/516/716 and similar).
It is based on the version 2 from Rolf Wagner from 2014.03.09 which can be found on [Arduino Playground][2]. The TSIC sensors feature a very high accuracy and can be read out roughly every 100ms using the ZACwire-rotocol, more informations can be found in the [datasheet][3]. Calcularions for different sensors as the 20x,30x, 50x and also the high accuracy 516/716 series are included, only a flag is needed to select the sensor type which is 20x/30x by default.
Calculations can be found in the manufacturer's [application note][4].
The code is optimized for high speed and low memory consumption. The calculation routines use constant integer calculations and bit shifts to save computing time which is in case of a standard Atmega328p roughly a factor of 1.5-2 at no loss of computational accuracy.

Installing the library
======================
For installation just download the contents of this repository into TSIC-folder inside your arduino/libraries and restart your Arduino-IDE. For more information check the examples !

Connecting your sensor
=====================
This part is pretty easy. The TSIC-Sensor needs 3 pins to be connected - Vcc, GND and Signal as shown in the datasheet. No pull-up resistors or additional components are needed, so this can be done in a plug-and-play-style, for example plugging the TO-92-Sensor to GND-13-12 of an Arduino UNO. Connect your sensor and configure the corresponding pins in the TSIC-constructor as shown in the example.
NEW feature: external powering is possible - simply connect your sensor to GND and an external VCC instead of your AVR-PIN for powering. Check the example for usage.

[1]: https://github.com/Schm1tz1/arduino-tsic
[2]: http://playground.arduino.cc/Code/Tsic
[3]: http://playground.arduino.cc/uploads/Code/TSIC_Datasheet.zip
[4]: https://www.ist-ag.com/sites/default/files/ATTSic_E.pdf

Status
======
This is the (non-stable) development version that still needs to be tested before it is added to the main branch. As the new 716 sensors are not yet available, a message was sent to the manufacturer to get a sample sensor for development. This code will be tested and merged as soon as a sensor is available and tested.
