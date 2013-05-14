LCD
===

Experiments with Arduino and I2C LCD

This project links an analogue linear 10K potentiometer to display an angle on the LCD.
The LCD is an I2C wired on the standard pins, in my case on the UNO, pins A4 (SDA), A5 (SCL)
See http://arduino.cc/en/Reference/Wire

Enhancements:

Check the previous value and if not changed then don't refresh, this would stop flickering
