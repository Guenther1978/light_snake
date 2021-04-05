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
  uint8_t _pointerMax = 240;
  bool _darker = true;
public:
  uint8_t getNumber();
  void setNumber(uint8_t);
  uint16_t getIntensity();
  void setIntensity(uint16_t);
  uint8_t getPointer();
  void setPointer(uint8_t);
  bool getDarker();
  void setDarker(bool);
  void increaseIntensity();
  void decreaseIntensity();
  void changeIntensity();
  void increasePointer();
  void decreasePointer();
  void changePointer();
  void changeDarker();
  void pointer2int();
};

#endif
