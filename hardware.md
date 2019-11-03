# Hardware v1.1 Description

## Hardware Features

### Power Switching
The main feature of the hotwire controller is the power switching module.
Two high performance N-channel MOSFETs are used to regulate the output voltage of the power module.
These MOSFETs form a low-side switch and are switched with a 62.5kHz PWM signal. The power module also includes a
low resistance, high capacitance RC filter to smooth the output voltage. This smoothing makes for cleaner
current sensing. The controller was not intended to be used with inductive loads and so there
is no flyback diode protection on this circuit.

### Current Sensing
This controller uses the INA219 current sensor with a 0.01 ohm shunt to measure
the electrical characteristics of the circuit. The sensor reports various voltages,
output current, and power dissipation of the power section over the I2C protocol.
Starting with the `v1.1.0` firmware, the device uses a programmable-gain PID
controller to modulate the duty cycle of the power stage based on the power reading
from the INA219.

### Rotary Encoder
The rotary encoder is the main avenue for interfacing with the controller. The encoder's two
channels and the encoder's switch are connected to the microcontroller through RC low-pass
filters for mild contact debouncing. Full debouncing is handled in the firmware of the microcontroller.

### LCD Backlight and Contrast
The LCD's backlight and contrast are adjustable through the use of PWM. Large ceramic capacitors
are used to smooth the PWM signals. There is one capacitor for the backlight signal and one capacitor
for the contrast signal. Both signals are connected to different channels of the same 8-bit timer.
The PWM duty cycles can be set dynamically by the user.

### External GPIO
The remaining used pins of the microcontroller are broken out to external headers for use with
custom hardware extension modules. Additional hardware features, such as external control switches
or sensors, can easily be integrated into the current hardware through the use of these GPIO pins.
GPIO pin 0 is also attached to a timer output for hardware PWM functionality.

## Microcontroller Pinout
All pins of the ATMega328P microcontroller are used on the board. The connections are defined as follows:

| MCU Port        | Connection        |
|-----------------|-------------------|
| PORTB0          | ENCODER_B         |
| PORTB1          | ENCODER_A         |
| PORTB2          | Hotwire_PWM       |
| PORTB3          | GPIO_0 / MOSI     |
| PORTB4          | GPIO_1 / MISO     |
| PORTB5          | GPIO_2 / SCK      |
| PORTB6          | XTAL_1            |
| PORTB7          | XTAL_2            |
| PORTC0          | LCD_DATA_3        |
| PORTC1          | LCD_DATA_2        |
| PORTC2          | LCD_DATA_1        |
| PORTC3          | LCD_DATA_0        |
| PORTC4          | SDA               |
| PORTC5          | SCL               |
| PORTC6          | RESET             |
| PORTD0          | LCD_ENABLE        |
| PORTD1          | LCD_RW            |
| PORTD2          | LCD_RS            |
| PORTD3          | BUZZER            |
| PORTD4          | GPIO_3            |
| PORTD5          | LCD_BACKLIGHT     |
| PORTD6          | LCD_CONTRAST      |
| PORTD7          | ENCODER_SWITCH    |
