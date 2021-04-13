#ifndef LIGHT_SNAKE_H
#define LIGHT_SNAKE_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Led.hpp"
#include "SpeedControl.hpp"

#define NUMBER_OF_LEDS 14
#define DALAY_TIME 100;
#define DURATION_MAX 3

class LightSnake
{
private:
  Led led[NUMBER_OF_LEDS];
  Adafruit_PWMServoDriver pwm;
  unsigned long old_millis;
public:
  /**@brief This function initializes the LightSnake class.
   *
   * The class contains one instance of the class
   * Adafruit_PWMServoDriver and an array of the
   * class Led. The random generator will be
   * initialized, too.
   */
  void setup();
  /**@brief This function repeats teh updates of
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
