#ifndef SPEED_CONTROL_H
#define SPEED_CONTROL_H

#include <Arduino.h>

class SpeedControl
{
private:
  uint8_t _number = 0;
  uint8_t _duration = 1;
  uint8_t _max_duration = 5;
  uint8_t _counter = 0;
  bool _trigger = false;
public:
  uint8_t getNumber();
  void setNumber(uint8_t);
  uint8_t getDuration();
  void setDuration(uint8_t);
  bool getTrigger();
  void count();
};

#endif
