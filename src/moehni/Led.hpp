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
  uint8_t _progmemIndex = 0;
  uint8_t _pointer = 0;
  uint8_t _pointerMax = 255;
  bool _darker = true;
  bool _darkerHasChanged = false;  
  bool _intensityAtMax = false;
  bool _intensityAtMin = false;
  bool _waitAtMinIntensity = false;
  bool _waitAtMaxIntensity = true;
  uint8_t _cyclesAtMinIntensity = 33;
  uint8_t _cyclesAtMaxIntensity = 33;
public:
  ///////////////////////
  // get ans set methods
  ///////////////////////

  // _number

  /**@return the number of the LED*/
  uint8_t getNumber();

  /**@param number of the LED*/
  void setNumber(uint8_t);

  
  // _intensity
  
  /**@return intensity of the LED*/
  uint16_t getIntensity();

  /**@param intensity of the LED*/
  void setIntensity(uint16_t);

  
  // _pointer
  
  /**@return pointer to the intensity table*/
  uint8_t getPointer();

  /**@param pointer to the intensities*/  
  void setPointer(uint8_t);

  /**@return pointer to the intensity table*/
  uint8_t getProgmemIndex();

  /**@param pointer to the intensities*/  
  void setProgmemIndex(uint8_t);
  

  // _darker

  /**@return darker of the LED*/
  bool getDarker();

  /**@param darker if the brightness of the LED decreases*/
  void setDarker(bool);

  /**@brief inverts darker*/
  void invertDarker();


  // _waitAtM??Intensity

  /**@return waitAtMinIntensity*/
  bool getWaitAtMinIntensity();

  /**@param waitAtMinIntensity this LED waits at its ninimal brightness*/
  void setWaitAtMinIntensity(bool);

  /**@return waitAtMaxIntensity*/
  bool getWaitAtMaxIntensity();

  /**@param WaitAtMaxIntensity this LED waits at its naximal brightness*/
  void setWaitAtMaxIntensity(bool);

  
  // _cyclesAtM??Intensity
  
  /**@return cyclesAtMinIntensity of the LED*/
  uint8_t getCyclesAtMinIntensity();

  /**@param cyclesAtMinIntensity this LED waits this cycles at its ninimal brightness*/
  void setCyclesAtMinIntensity(uint8_t);

  /**@return cyclesAtMaxIntensity this LED waits at its ninimal brightness*/
  uint8_t getCyclesAtMaxIntensity();

  /**@param cyclesAtMaxIntensity this LED waits this cycles at its maximal brightness*/
  void setCyclesAtMaxIntensity(uint8_t);


  // _darkerHasChanged, _intensityAtMax, intensityAtMin
  
  /**@return _darkerHasChanged*/
  bool getDarkerHasChanged();

  /**@return _intensityAtMin*/
  bool getIntensityAtMin();

  /**@return _intensityAtMax*/
  bool getIntensityAtMax();
  
  //////////////////////////////////////
  // methods dealing with the intensity
  //////////////////////////////////////
  
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


  ///////////////////////////////////////////////////////
  // methods dealing with the pointer to thw intensities
  ///////////////////////////////////////////////////////
  
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

  
  ////////////////////////////////////////////////
  // methods dealing with the class SpeedControl
  ////////////////////////////////////////////////

  /**@brief Call counter method of class SpeedControl
   *
   * The property counter of the aggregated class SpeedControl
   * is decreased. If its value is equal to zero, true is returned.
   * The variable is the initialized with the duration. 
   */
  bool letSpeedControlCount();

  /**@param duration time at one intensity (property of the class SpeedControl)*/
  void setSpeedControlDuration(uint8_t);

  /**@return duration (the time at one intensity, property of the class SpeedControl)*/
  uint8_t getSpeedControlDuration();
  
  /**@param counter
   *
   * If a longer duration is wanted, the counter can be set to
   * a value greater than duration.
   */
  void setSpeedControlCounter(uint8_t);

  /**@return counter counts from duration to zero*/
  uint8_t getSpeedControlCounter();
};

#endif
