#include "Led.hpp"

///////////////////////
// get ans set methods
///////////////////////

// _number

uint8_t Led::getNumber()
{
  return _number;
}

void Led::setNumber(uint8_t number)
{
  _number = number;
}


// _intensity

uint16_t Led::getIntensity()
{
  return _intensity;
}

void Led::setIntensity(uint16_t intensity)
{
  _intensity = intensity;
}


// _pointer

uint8_t Led::getPointer()
{
  return _pointer;
}

void Led::setPointer(uint8_t pointer)
{
  _pointer = pointer;
}


// _darker

bool Led::getDarker()
{
  return _darker;
}

void Led::setDarker(bool darker)
{
  _darker = darker;
}

void Led::invertDarker()
{
  _darker != _darker;
}


// _waitAtM??Intensity

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


// _cyclesAtM??Intensity

uint8_t Led::getCyclesAtMinIntensity()
{
  return _cyclesAtMinIntensity;
}

void Led::setCyclesAtMinIntensity(uint8_t cyclesAtMinIntensity)
{
  _cyclesAtMinIntensity = cyclesAtMinIntensity;
}

uint8_t Led::getCyclesAtMaxIntensity()
{
  return _cyclesAtMaxIntensity;
}

void Led::setCyclesAtMaxIntensity(uint8_t cyclesAtMaxIntensity)
{
  _cyclesAtMaxIntensity = cyclesAtMaxIntensity;
}


// _darkerHasChanged, _intensityAtMax, intensityAtMin

bool Led::getDarkerHasChanged()
{
  return _darkerHasChanged;
}

bool Led::getIntensityAtMin()
{
  return _intensityAtMin;
}

bool Led::getIntensityAtMax()
{
  return _intensityAtMax;
}


//////////////////////////////////////
// methods dealing with the intensity
//////////////////////////////////////

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


///////////////////////////////////////////////////////
// methods dealing with the pointer to the intensities
///////////////////////////////////////////////////////

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


////////////////////////////////////////////////
// methods dealing with the class SpeedControl
////////////////////////////////////////////////

bool Led::letSpeedControlCount()
{
  return speedControl.count();
}

void Led::setSpeedControlDuration(uint8_t duration)
{
  speedControl.setDuration(duration);
}

uint8_t Led::getSpeedControlDuration()
{
  return speedControl.getDuration();
}

void Led::setSpeedControlCounter(uint8_t counter)
{
  speedControl.setCounter(counter);
}

uint8_t Led::getSpeedControlCounter()
{
  return speedControl.getCounter();
}
