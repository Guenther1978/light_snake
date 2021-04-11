#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "intensities.h"

class Led
{
private:
  uint8_t _number = 0;
  uint16_t _intensity = 0;
  uint16_t _intensityMin = 0;
  uint16_t _intensityMax = 4095;
  uint8_t _pointer = 0;
  uint8_t _pointerMax = 255;
  bool _darker = true;
  bool _darkerHasChanged =false;
public:
  /**@return the number of the LED*/
  uint8_t getNumber();

  /**@param sets the number of the LED*/
  void setNumber(uint8_t);

  /**@return the intensity of the LED*/
  uint16_t getIntensity();

  /**@param sets the number of the LED*/
  void setIntensity(uint16_t);

  /**@return the pointer to the intensity table*/
  uint8_t getPointer();

  /**@param sets the number of the LED*/  
  void setPointer(uint8_t);

  /**@return the member _darker of the LED*/
  bool getDarker();

  /**@param sets the number of the LED*/
  void setDarker(bool);

  /**@return the number of the LED*/
  bool getDarkerHasChanged();
  
  /**Increases the member _intensity.
   * This method also compares the _intensity member
   * with its limits.
   */
  void increaseIntensity();

  /**Decreases the member _intensity.
   * This method also compares the _intensity member
   * with its limits.
   */
  void decreaseIntensity();

  /**Increases or devreases the member _intensity.*/
  void changeIntensity();

  /**Increases the pointer to the intensities.*/
  void increasePointer();

  /**Decreases the pointer to the intensities.*/
  void decreasePointer();

  /**Increases or devreases the member _pointer.*/
  void changePointer();

  /**Inverts the boolean member _darker.*/
  void changeDarker();

  /**Reads the content of the PROGMEM array.*/
  void pointer2int();
};

#endif
