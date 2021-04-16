#ifndef LIGHT_SNAKE_H
#define LIGHT_SNAKE_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Led.hpp"
#include "SpeedControl.hpp"

#define NUMBER_OF_LEDS 14
#define DELAY_TIME 30
#define DURATION_MAX 3
#define FULL_INTENSITY 4095
#define DELAY_TEST 1000

class LightSnake
{
private:
  Led led[NUMBER_OF_LEDS];
  Adafruit_PWMServoDriver pwm;
  unsigned long old_millis;
  byte incomingByte;
public:
  /**@brief This method prints an info
   *
   * The Serial Monitor of the Arduino IDE, PuTTY or picocom
   * can be used.\
   * H: Help\
   * I: Info\
   * J: Test all LEDs
   * K: Test a single LED
   * X: Continue agter testing single LEDs
   */
  void help();

  /**@brief This methode prints the info of all Leds
   *
   * Number: number of the LED\
   * Intensity: intensity of the LED\
   * Darker: Is the intesity increasing or decreasing?\
   * Duration: cycles at an intensity\
   * Counter: vakue of the counter, counts down from
   * duration to zero.
   */
  void info();

  /**@brief Clear all LEDs
   *
   * All LEDs are cleared by sending the intesnity
   * Zero to the PCA9685
   */
  void clearAllLEDs();

  /**@brief Gets he number of the LED to test.
   *
   * Get the number of the LED to test.
   * Hexadecimal number are used:\
   * 0 1 2 3 4 5 6 7 8 9 A B C D\
   * X will delete this loop.
   */
  void getLEDNumber();
    
  /**@brief This method tests the specified LED.
   *
   * First all LED are turned off. After waiting for a second,
   * the specified LED is turned on for a second and then
   * turned off.
   * So the hardware can be tested.
   * The Serial Monitor of the Arduino IDE, PuTTY or picocom
   * can be used.
   */
  void testLED(uint8_t);
    
  /**@brief This method tests the LEDs and their current sources.
   *
   * Every LED is beeing tested after this method is called.
   * First all LED are turned off. After waiting for a second,
   * every LED is turned on for a second and then turned off.
   * After waiting for a second, the next LED is turnde on and
   * off. So the hardware
   * can be tested. Very helpful at startup or in finding bugs.
   * This method can be started by sending a 't' to the USART.
   */
  void testAllLEDs();
  
  /**@brief This function initializes the LightSnake class.
   *
   * The class contains one instance of the class
   * Adafruit_PWMServoDriver and an array of the
   * class Led. The random generator will be
   * initialized, too.
   */
  
  void setup();
  /**@brief This function repeats the updates of
   * the intensites of the leds.
   *
   * Every element of the Led Class is called. Their
   * intensities are updated and at the min or max value
   * a new duration of the speed is evaluated. The new
   * intensities are send via the I2C bus to the PCA9685.
   */
  void loop();
};

#endif
