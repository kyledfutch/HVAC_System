# EML4804 Spring 2025 - Project 1: Thermostat Control System
## Overview
Using a TMP36 analog temperature sensor, create a simple thermostat control
device for a heat pump HVAC system
### The system input is done by means of 9 input wires as follows:
- Input wire for turning the system on/off, with 5v turning on the system and
0v turning off the system.
- Input wire to set the system to heating mode, 5v, or to cooling mode, 0v.
- Seven input wires to set the desired temperature between 0 and 127
degrees.
- TMP36 sensor to provide the system with room temperature.
### System output is done by means of 11 LEDs as follows:
- A green LED that is on when the system is on and off when the system is
off.
- Two LEDs, one red and one green, to indicate when the system is in heat or
cool mode. Only one can be on at a time with red indicating heat mode and
green indicating cooling mode.
- One yellow LED to turn on and off as the fan is turned on and off.
- Seven LEDs to indicate the current temperature as being read by the
TMP36 sensor.
### System operations and constraint:
- If temp difference between desired and measured temp is more than 2
then the system starts either cooling or heating as desired. The fan light
indicates the system is running.
- If the system is turned off, the fan should stay on for 15 seconds (system
cool down procedure).
- If the system is turned off and then back on before 30 seconds has elapsed
then it should not come back on (fan light on) till the 30 seconds had
passed.
- Switching directly from heat to cool and vice versa, if the system is on at
the time, requires a cool down period (fan is off) for 30 seconds between
these switching.

## Components Used
- Arduino Mega2560
- TMP36 Temperature Sensor
- 11 LEDs (Green, Yellow, Red)
- Resistors
- Breadboards
- Wiring
