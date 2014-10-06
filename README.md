[arduino-tsic][1]
============
This project is a library for TSIC digital temperature sensors (type 206/306 and similar). It is based on the version 2 from Rolf Wagner from 2014.03.09 which can be found on [Arduino Playground][2]. The TSIC sensors feature a very hich accuracy and can be read out roughly every 100ms using the ZACwire-rotocol, more informations can be found in the [datasheet][3]. The code is optimized for high speed and low memory consumption as described in the release notes from version 2:

- Arduino > 1.0 compatible
- corrected offset (about +2°C)
- code run time optimization
- no freezing of system in case sensor gets unplugged
- measure strobetime instead of constant waiting time (-> high temperature stable)
- code cleanup
- space optimization, now only 239 byte

Installing the library
======================
For installation just download the contents of this repository into TSIC-folder inside your arduino/libraries and restart your Arduino-IDE. For more information check the examples !

Connecting your sensor
=====================
This part is pretty easy. The TSIC-Sensor needs 3 pins to be connected - Vcc, GND and Signal as shown in the datasheet. No pull-up resistors or additional components are needed, so this can be done in a plug-and-play-style, for example plugging the TO-92-Sensor to GND-13-12 of an Arduino UNO. Connect your sensor and configure the corresponding pins in the TSIC-constructor as shown in the example.

[1]: https://github.com/Schm1tz1/arduino-tsic
[2]: http://playground.arduino.cc/Code/Tsic
[3]: http://playground.arduino.cc/uploads/Code/TSIC_Datasheet.zip
