#include "Led.hpp"

uint8_t Led::getNumber()
{
  return _number;
}

void Led::setNumber(uint8_t number)
{
  _number = number;
}

uint16_t Led::getIntensity()
{
  return _intensity;
}

void Led::setIntensity(uint16_t intensity)
{
  _intensity = intensity;
}

uint8_t Led::getPointer()
{
  return _pointer;
}

void Led::setPointer(uint8_t pointer)
{
  _pointer = pointer;
}

bool Led::getDarker()
{
  return _darker;
}

void Led::setDarker(bool darker)
{
  _darker = darker;
}

bool Led::getWaitAtMinIntensity()
{
  return _waitAtMinIntensity;
}

void Led::setWaitAtMinIntensity(bool waitAtMinIntensity)
{
  _waitAtMinIntensity = waitAtMinIntensity;
}

bool Led::getWaitAtMaxIntensity()
{
  return _waitAtMaxIntensity;
}

void Led::setWaitAtMaxIntensity(bool waitAtMaxIntensity)
{
  _waitAtMaxIntensity = waitAtMaxIntensity;
}

bool Led::getDarkerHasChanged()
{
  return _darkerHasChanged;
}

void Led::increaseIntensity()
{
  _intensity ++;
  if (_intensity == _intensityMax)
    {
      _intensityAtMin = false;
      _intensityAtMax = true;
      _darker = true;
      _darkerHasChanged = true;
    }
}

void Led::decreaseIntensity()
{
  _intensity --;
  if (_intensity == _intensityMin)
    {
      _intensityAtMin = true;
      _intensityAtMax = false;
      _darker = true;
      _darkerHasChanged = true;
    }
}

void Led::changeIntensity()
{
  _darkerHasChanged = false;
  if (_darker)
    {
      decreaseIntensity();
    }
  else
    {
      increaseIntensity();
    }
}

void Led::increasePointer()
{
  _pointer ++;
  if (_pointer == _pointerMax)
    {
      _intensityAtMin = false;
      _intensityAtMax = true;
      _darker = true;
      _darkerHasChanged = true;
    }
}

void Led::decreasePointer()
{
  _pointer --;
  if (_pointer == 0)
    {
      _intensityAtMin = true;
      _intensityAtMax = false;      
      _darker = false;
      _darkerHasChanged = true;
    }
}

void Led::changePointer()
{
  _darkerHasChanged = false;
  if (_darker)
    {
      decreasePointer();
    }
  else
    {
      increasePointer();
    }
}

void Led::pointer2int()
{
  _intensity = pgm_read_word_near(intensities + _pointer);
  if (_intensity <= _intensityMin)
    {
      _intensity = _intensityMin;
    }
  if (_intensity >= _intensityMax)
    {
      _intensity = _intensityMax;
    }
}

bool Led::letSpeedControlCount()
{
  return speedControl.count();
}

void Led::setSpeedControlDuration(uint8_t duration)
{
  speedControl.setDuration(duration);
}

void Led::setSpeedControlCounter(uint8_t counter)
{
  speedControl.setCounter(counter);
}
/*
void Led::update()
{
  speedControl.count();
  if (speedControl.getTrigger())
    {
      changePointer();
      pointer2int();
      if (_darkerHasChanged)
        {
          speedControl.setDuration(random(1, 3));
          if (_intensityAtMax && _waitAtMaxIntensity)
            {
              speedControl.setCounter(_cyclesAtMax);
            }
          if (_intensityAtMin && _waitAtMinIntensity)
            {
              speedControl.setCounter(_cyclesAtMax);
            }
        }
    }
}
*/
