#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "intensities.h"
#include "SpeedControl.hpp"

class Led
{
private:
  SpeedControl speedControl;
  uint8_t _number = 0;
  uint16_t _intensity = 0;
  uint16_t _intensityMin = 1000;
  uint16_t _intensityMax = 4095;
  uint8_t _pointer = 0;
  uint8_t _arraySize = 255;
  bool _darker = true;
  bool _darkerHasChanged = false;  
  bool _intensityAtMax = false;
  bool _intensityAtMin = false;
  bool _waitAtMinIntensity = false;
  bool _waitAtMaxIntensity = true;
  uint8_t _cyclesAtMin = 10;
  uint8_t _cyclesAtMax = 10;
public:
  /**@return the number of the LED*/
  uint8_t getNumber();

  /**@param number*/
  void setNumber(uint8_t);

  /**@return the intensity of the LED*/
  uint16_t getIntensity();

  /**@param intensity*/
  void setIntensity(uint16_t);

  /**@return the pointer to the intensity table*/
  uint8_t getPointer();

  /**@param pointer*/  
  void setPointer(uint8_t);

  /**@return the member _darker of the LED*/
  bool getDarker();

  /**@param darker*/
  void setDarker(bool);

  /**@return the member _darker of the LED*/
  bool getWaitAtMinIntensity();

  /**@param setWaitAtMinIntensity*/
  void setWaitAtMinIntensity(bool);

  /**@return the member _darker of the LED*/
  bool getWaitAtMaxIntensity();

  /**@param setWaitAtMaxIntensity*/
  void setWaitAtMaxIntensity(bool);

  /**@return */
  bool getDarkerHasChanged();
  
  /**Increases the intensity.
   *
   * If the new intensity is equal to the maximal intensity,
   * the intensities will be decreased in the next step.
   */
  void increaseIntensity();

  /**Decreases the intensity.
  *
  * If the new intensity is equal to the minimal intensity,
  * the intensities will be increased in the next step.
  */
  void decreaseIntensity();

  /**@brief Increases or decreases the member _intensity.
   *
   * In dependency of the boolean value of darker the method
   * increaseIntesity or decreaseIntensity is called.
   */
  void changeIntensity();

  /**Increases the pointer to the intensities.
   *
   * If the new value of the pointer is equal
   * to the size of the array,
   * the pointer will be decreased in the next step;
   */
  void increasePointer();

  /**Decreases the pointer to the intensities.
  *
  * If the new value of the pointer is equal
  * to zero, the pointer will be increased in the next step.
  */
  void decreasePointer();

  /**Increases or decreases the pointer.
   *
   * In dependency of the boolean value of darker the method
   * increasePointer or decreasePointer is called.
   */
  void changePointer();

  /**@return the content of the PROGMEM array.
   *
   * The array with the intensitys is included in the header file
   * 'intensities.h'. This file has been created by the python
   * script 'progmen_creator.py'.
   */
  void pointer2int();

  /**@brief Call counter method of class SpeedControl
   *
   * The property counter of the aggregated class SpeedControl
   * is decreased. If its value is equal to zero, true is returned.
   * The variable is the initialized with the duration. 
   */
  bool letSpeedControlCount();

  /**Sets a duration property of the class SpeedControl
   *
   * This variable initializes the property counter.
   */
  void setSpeedControlDuration(uint8_t);

  /**@brief counter
   *
   * If the a longer duration is wanted, the counter can be set to
   * a value greater than duration.
   */
  void setSpeedControlCounter(uint8_t);
};

#endif
