# Heddy-OS
#### By Mathias Hedberg
[Heddy-OS](https://github.com/metrafonic/Heddy-OS) is A set of libraries and main file, to run a basic OS on the ATmega32 with an LCD.
The system uses a custom LCD library for a 16x2 LCD display. 

![](http://metrafonic.com/content/images/2015/05/99999.jpg)

Usage of Heddy-OS is easy. Two buttons connecten via PINC0 and PINC1 allow the user to navigate sideways in the menu, select functions, perform actions in these functions, and exit back to the main menu.

Heddy-OS Currently features:

 - Contrast Dialog, to read the contrast level via ADC
 - About Screen with smart scrolling text that senses when it is optimal to start a new line, or clear the screen when the screen is full.
 - Backlight Control allows the user to turn off and on the pin that is controlling the LED backlight
 - UART Transmitter, displaying the current baud rate. Users can press the next button to send out a signal via UART.
 - UART Reciever, displaying the current baud rate. Users will be notified of incoming signals via a counter on screen.
 - Simple buzzer beep each time a button is pressed, alarm sound when the alert function is called
 - More to come!

A schematic for the connections is still in the works. A quick summary is the only option at the moment:

* LCD data pins: PortB (PB0 through to PB7)
* LCD contrast: Potentiometer connected to GND and Vcc
* LCD control pins: Port D as the following:
 * RS: PD2
 * Read/Write: PD7
 * Enable: PD5
* LCD Backlight +: PINC7
* Button Select/Cancel: PC1 through to GND
* Button Next/Change: PC0 through to GND
* ADC0: Potentiometer/LCD Contrast
* UART Receive: RX pin (PD0)
* UART Transmit: TX pin (PD1)


Feel free to branch this project.

GitHub: https://github.com/metrafonic/Heddy-OS
