/**@file */

#ifndef LIGHT_SNAKE_H
#define LIGHT_SNAKE_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <EEPROM.h>
#include "Led.hpp"
#include "SpeedControl.hpp"

#define NUMBER_OF_LEDS 14
#define NUMBER_OF_PROGMEMS 4
#define DELAY_TIME 20
#define DURATION_MAX 3
#define FULL_INTENSITY 4095
#define DELAY_TEST 1000
#define ASCII_OFFSET 48
#define ADDRESS_LOOP_TIME 0
#define ADDRESS_PROGMEM_INDEX 1

class LightSnake
{
private:
  Led led[NUMBER_OF_LEDS]; /**< Array of instances of the class Led */
  Adafruit_PWMServoDriver pwm; /**< An instance of the class Adafrui_PWMServoDriver*/
  unsigned long cycleTime;
  unsigned long loopDuration;
  unsigned long oldMillis;
  bool outputOfLoopDuration;
  byte incomingByte;
public:
  /**@brief This function initializes the LightSnake class.
   *
   * The class contains one instance of the class
   * Adafruit_PWMServoDriver and an array of the
   * class Led. The random generator and the class
   * Serial will be initialized, too.
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

  /**@brief This method prints an info
   *
   * The Serial Monitor of the Arduino IDE, PuTTY or picocom
   * can be used.
   */
  void help();

  /**@brief This methode prints the info of all Leds
   *
   * The number, intesity, darker and duration of
   * all LEDs are printed. And the time each the last
   * loop has needed and the cycle time of the loop.
   */
  void info();

  /**@brief Clear all LEDs
   *
   * All LEDs are cleared by sending the intensity
   * Zero to each chanel of the PCA9685
   */
  void clearAllLEDs();

  /**@return number
   *
   * This method is used by getting the number of a
   * LED and by getting the new duration.
   */
  int8_t getNumber();
  
  /**@brief Gets he number of the LED to test.
   *
   * Get the number of the LED to test.
   * Hexadecimal number are used
   * (0..9, A, B, C, D).
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
   * off. So the hardware can be tested.
   */
  void testAllLEDs();

  /**@brief This method handels the output of the loop time.
   *
   * The output of the looptime, the duration of an cycle,
   * can be enabled or disabled. Every time when this method
   * is called, the corresponding boolean varialble is inverted.
   */
  void invertOutputOfLoopDuration();

  /**@brief This method sets a new duration time for the loop.
   *
   * The time sets the duration for the loop. If this value is
   * to small, the function will not wait and start immediately
   * with the next cycle.
   * After each cycle the methods waits till the duration of
   * a cycle is over. A loop duration can be set with a
   * char. This character represent a hexadecimal digit.
   * Hexadecimal number are used (0..9, A, B, C, D, E, F).
   * The new duration time is this digit multiplied by 5 ms.
   * At the end of the loop, the output of millis() is polled.
   * If the value 0 is choosen, the next loop starts immediately.
   */
  void changeLoopDuration();

  /**@brief This methods sets the beginning of an array.
   *
   * There can be different arrays containing the intensities.
   * With this method the index of the progmem is set globally
   * for all LEDs.
   */
  void setIndex();

  /**@brief This method reads the content of the EEPROM.
   *
   * The user can set the cycle time and the index of the
   * used PROGMEM. The setup function can read the stored
   * values.
   */
  void readEeprom();

  /**@brief This methods writes the current values to the EEPROM.
   *
   * If the user changed the loop time and the PROGMEM index,
   * he can save this to the EEPROM. So they will be loaded at
   * the next start.
   */
  void writeEeprom();
};

#endif
