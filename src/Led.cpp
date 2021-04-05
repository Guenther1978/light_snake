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

void Led::increaseIntensity()
{
  _intensity ++;
  if (_intensity == _intensityMax)
    {
      _darker = true;
    }
}

void Led::decreaseIntensity()
{
  _intensity --;
  if (_intensity == _intensityMin)
    {
      _darker = false;
    }
}

void Led::changeIntensity()
{
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
      _darker = true;
    }
}

void Led::decreasePointer()
{
  _pointer --;
  if (_pointer == 0)
    {
      _darker = false;
    }
}

void Led::changePointer()
{
  if (_darker)
    {
      decreasePointer();
    }
  else
    {
      increasePointer();
    }
}

void Led::changeDarker()
{
  _darker != _darker;
}

void Led::pointer2int()
{
  _intensity = pgm_read_word_near(intensities + _pointer);
  if (_intensity < _intensityMin)
    {
      _intensity = _intensityMin;
    }
}
