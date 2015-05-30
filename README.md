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
 - More to come!

Feel free to branch this project.

GitHub: https://github.com/metrafonic/Heddy-OS
