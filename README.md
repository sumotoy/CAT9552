CAT9552
=======

An easy Arduino/Teensy3/Energia library for ON semiconductors CAT 9552 led driver.
Tested with Arduino/Teensy3.x, not with Energia, btw it compiles.

This chip has 2 internal timers so every single led can be:

 - off
 - on
 - blinking 1 (as timer1 settings)
 - blinking 2 (as timer2 settings)

The chip works in I2C and library take care of everithing, see example.
Please note that I2C initializations are outside library (to prevent multiple initializations) so check the example for more infos. It can be used as GPO (no input)!

Chip description

The CAT9552 is a 16−channel, parallel input/output port expander
optimized for LED On/Off and blinking control. Each individual LED
may be turned ON, OFF, or set to blinking at one of two programmable
rates. The CAT9552 is compatible with I2C and SMBus applications
where it is desireable to limit the bus traffic or free−up the bus master’s
internal timer. Three address pins allow up to eight CAT9552 devices
to occupy the same bus.
The CAT9552 contains an internal oscillator and two PWM signals,
which drive the LED outputs. The user may program the period and
duty cycle for each individual PWM signal. After an initial set−up
command to program the Blink Rate 1 and Blink Rate 2 (frequency
and duty cycle), only one command from the bus master is required to
turn each individual open drain output ON, OFF, or cycle at Blink
Rate 1 or Blink Rate 2. Each open drain LED output can sink a
maximum current of 25 mA. The total continuous current sunk by all
I/Os must not exceed 200 mA per package.
