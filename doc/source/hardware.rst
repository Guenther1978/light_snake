Hardware
========

This light sculpture includes 15 power LEDs. Each power LED has its own current source_.

.. _source: http://led-treiber.de/html/getaktete_treiber.html#Treiber-555-MOSFET

Each current source contains a NE555 working as a two-level controller. The average value
of the current is 300 mA. The pin 4 of a NE555 is a reset pin, which can be used for
intensity control via PWM.

To control all 14 current sources the PCA9685_ is used. This IC is controlled by an
Arduino_.

.. _PCA9685: https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/ic-led-controllers/16-channel-12-bit-pwm-fm-plus-ic-bus-led-controller:PCA9685

.. _Arduino: https://www.arduino.cc/
