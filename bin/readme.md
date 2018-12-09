# Test Binaries

These binaries were compiled using this hotwire controller library.
The purpose of these binaries is to test certain functions to verify
the functionality of the circuit and to find problems associated
with the design of the PCB.

### outout\_toggle.hex
* Conditions: Supply power to battery rails of PCB. Connect probes to wire side
connector. 
* Expected Result: Circuit should output a square wave with a 100ms width.
* Notes: 5v LED should come on when power is connected. 

### buzzer.hex
* Conditions: Supply 5v to MCU in any way. Probe buzzer.
* Expected Result: Buzzer should output an audible tone at 500Hz at a
reasonable volume. 
* Notes: 5v LEDs should come on with power. 
