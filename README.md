# RainbowCycle
My very first circuit board. I'm very proud to say that the first fabrication of it worked! :)

The PCB was fabricated by Seeedstudio: http://www.seeedstudio.com/service/

Components on the board were hand soldered by me.

## YouTube Video
<a href="http://www.youtube.com/watch?feature=player_embedded&v=ZXkaFkIlUeY
" target="_blank"><img src="http://img.youtube.com/vi/ZXkaFkIlUeY/0.jpg" 
alt="RainbowCycle YouTube Video"/></a>

## Bill of materials
* 10x Common Anode RGB LEDs - 5mm Square (Sometimes called 'Super flux' or 'Piranha') 
* 1x ATMega328P-PU - same chip used by the Arduino Uno
* 2x TLC5940s - 16 Channel LED Driver
* 2x 10K Ohm Potentiometers - adjustable speed and brightness
* 2x 2K Ohm Resistors - current limiting for LED drivers
* 2x 10K Ohm Resistors - pull-up resistors for the ICs
* 1x 100uF Capacitor - filtering capacitor for stable power to ICs
* 3x 0.1uF Capacitors - also filtering capacitors for each IC
* 1x 16MHz Crystal - clock input for ATMega328P-PU
* 2x 22pF Capacitors - used by the 16MHz crystal
* 1x Mini-USB Connector - for power only, doesn't program Arduino
* 1x ISP Header - for programming the ATMega328P-PU
* 1x Terminal Blocks 5.08mm - alternative connector for power
* 1x Diode - protection against reverse polarity on block terminal

## Things I'd do differently if I wanted to revise the board

* Use trimpots that are flush with the board instead of panel mount potentiometers. Even when soldered on both sides of the board, the currently used potentiometers bend easily.
* Replace ATMega328P-PU with a microcontroller that can be programmed directly through USB. ICSP was a hassle, and I couldn't find a through-hole means of converting USB to serial.
* Provide overvoltage protection, or at least put a warning on the silkscreen that the circuit is only rated for 5V.
* Make pads on some components slightly bigger for some components, like resistors and small capacitors.
* Use slightly higher clearance for ground plane (maybe?).
