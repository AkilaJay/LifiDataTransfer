# LIFI Data Transfer

### Objective
Come up with an algorithm to transfer data using a LED and a photoresistor. 

### LIFI Transmission
This algorithm can can provide data rates upto 3000 bits/second with a single LED. The algorithm involves first setting the LED to 150, and then deciding a range around 150 (min and max) that the light reading can't go above or below. 

When a 1 is transmitted, the LED is set to 255. At the receiver, if we see an increase in the light reading, we record that as 1. If it is a decrease, it is recorded as a 0. If it surpasses the max or min values, we reset it to 150, and resend the data.

Only one Arduino is used in this, therefore, the receiver and the transmitter has to happen synchronously. If two separate devices are to be used, a commom period or rate of transmission can be established instead. 

### Items Needed

* Arduino Uno
* LDR (photoresistor)
* 1 kilo-ohm resistor
* LED

### Schematic
![Schematic](https://github.com/AkilaJay/LifiDataTransfer/blob/master/Images/Sketch.png?raw=true "Schematic of the project")

### Image

![Image](https://github.com/AkilaJay/LifiDataTransfer/blob/master/Images/image.jpg?raw=true " Project Image")

### License
MIT

