# Hardware Task List
* Machine the aluminum enclosure
* Solder the XT60 connector

## Modifications for v1.1
* Use a standard AC/DC adapter and DC barrel jack instead of a battery and XT60
* Correct the width of the board for the enclosure
* Fix the LCD voltage divider...
* Increase the isolate on the pours
* Leave unused ATMega pins unconnected (use internal pullups instead)
* Reassign all PWM pins to make actual sense...
* Put the LCD backlight on a PWM pin for an adjustable backlight
* Move the buzzer to the right to make mounting the heatsink easier
* Maybe move to a different clock source (crystal can is bulky and exprensive)
* Make the ground plane more directed for the return path on the MOSFET
