#include "SpeedControl.hpp"

uint8_t SpeedControl::getNumber()
{
  return _number;
}

void SpeedControl::setNumber(uint8_t number)
{
  _number = number;
}

uint8_t SpeedControl::getDuration(void)
{
  return _duration;
}

void SpeedControl::setDuration(uint8_t duration)
{
  _duration = duration;
}

bool SpeedControl::getTrigger(void)
{
  return _trigger;
}

void SpeedControl::count()
{
  _trigger = false;
  _counter --;
  if (!_counter)
    {
      _counter = _duration;
      _trigger = true;
    }
}
