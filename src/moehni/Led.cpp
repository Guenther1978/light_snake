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

bool Led::getDarkerHasChanged()
{
  return _darkerHasChanged;
}

void Led::increaseIntensity()
{
  _intensity ++;
  if (_intensity == _intensityMax)
    {
      changeDarker();
    }
}

void Led::decreaseIntensity()
{
  _intensity --;
  if (_intensity == _intensityMin)
    {
      changeDarker();
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
      changeDarker();
    }
}

void Led::decreasePointer()
{
  _pointer --;
  if (_pointer == 0)
    {
      changeDarker();
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

void Led::changeDarker()
{
  _darker != _darker;
  _darkerHasChanged = true;
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
