README for ESC_calib-test-arduino.ino
02.12.2016

This is a routine to test the command of an ESC Afro12A via arduino.

It starts with a calibration of the ESC, needed to inform the ESC of the min and max values that the arduino will use.

In that sketch, the ESC is told that arduino will send 1000 µs PWM pulse width for the min throttle and 2000 µs for full throttle.

After the calibration, a loop allows user to send any value within the range, to check the good operation of the arduino + ESC + brushless motor.
