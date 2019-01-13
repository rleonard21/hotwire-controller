# Test Binaries

These binaries were compiled using this hotwire controller library.
The purpose of these binaries is to test certain functions to verify
the functionality of the circuit and to find problems associated
with the design of the PCB.

## General Notes 
* 5v indicator LED on top right of board should come on with power.
* SCK indicator LED should flash when programs are uploaded.
* If connected, LCD backlight should come on with power. 

### outout\_toggle.hex
* Conditions: Supply power to battery rails of PCB. Connect probes to wire side
connector. 
* Expected Result: Circuit should output a square wave with a 100ms width 
(100.1ms benchmark).
* Description: The MOSFET output is toggled every 100ms using a busy-wait delay.

### buzzer.hex
* Conditions: Supply 5v to MCU in any way. Probe buzzer.
* Expected Result: Buzzer should output an audible tone at 500Hz at a
reasonable volume. Probe should indicate 500Hz square wave
(497.60 Hz benchmark).
* Description: Buzzer is supplied a CTC-type PWM signal at 500Hz.

## To-Do:
* MOSFET port PWM
* LCD character writing  
* Encoder push button
* Encoder decoding
* INA219 current/power reading
