#include "LightSnake.hpp"

void LightSnake::setup()
{
  pwm.begin();
  pwm.setPWMFreq(1600);
  
  for (uint8_t i = 0; i < NUMBER_OF_LEDS; i ++)
  {
    led[i].setNumber(i);
  }

  oldMillis = millis();
  cycleTime = DELAY_TIME;
  outputOfLoopDuration = false;

  randomSeed(analogRead(0));
  Serial.setTimeout(TIMEOUT);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Setup completed");
  Serial.println();
}

void LightSnake::loop()
{
  for (uint8_t i = 0; i < NUMBER_OF_LEDS; i ++)
  {
    if (led[i].letSpeedControlCount())
    {
      led[i].changePointer();
      led[i].pointer2int();
      if (led[i].getDarkerHasChanged())
      {
        led[i].setSpeedControlDuration(random(DURATION_MAX) + 1);
        if (led[i].getIntensityAtMax() && led[i].getWaitAtMaxIntensity())
          {
            led[i].setSpeedControlCounter(led[i].getCyclesAtMaxIntensity());
          }
          else if (led[i].getIntensityAtMin() && led[i].getWaitAtMinIntensity())
          {
            led[i].setSpeedControlCounter(led[i].getCyclesAtMinIntensity());
          }
      }
      pwm.setPWM(led[i].getNumber(), 0, led[i].getIntensity());
    }
  }
  loopDuration = millis() - oldMillis;
  if (outputOfLoopDuration)
    {
      Serial.print(loopDuration);
      Serial.print(", ");
    }
  while (millis() < (oldMillis + cycleTime));
  oldMillis = millis();
  if (Serial.available())
    {
      incomingByte = Serial.read();
      switch (incomingByte)
        {
        case 'h':
        case 'H':
          help();
          break;
        case 'i':
        case 'I':
          info();
          break;
        case 'j':
        case 'J':
          testAllLEDs();
          break;
        case 'k':
        case 'K':
          getLEDNumber();
          break;
        case 'l':
        case 'L':
          invertOutputOfLoopDuration();
          break;
        case 'm':
        case 'M':
          changeLoopDuration();
          break;
        case 'n':
        case 'N':
          setIndex();
          break;
        default:
          break;
        }
    }
}

void LightSnake::help()
{
  Serial.println();
  Serial.println("h: Help");
  Serial.println("i: Info");
  Serial.println("j: Test all LEDs");
  Serial.println("k: Test a single LED");
  Serial.println("x: continue after testing single LEDs");
  Serial.println("l: enable and disable output of the loop time");
  Serial.println("m: Change the duration of the loop");
  Serial.println("n: Set a new intensity array");
  Serial.println();
}

void LightSnake::info()
{  
  Serial.println();
  Serial.println("number\tintensity\tdarker\tduration\tcounter");
  for(int i = 0; i < NUMBER_OF_LEDS; i++)
    {
      Serial.print(led[i].getNumber());
      Serial.print("\t");
      Serial.print(led[i].getIntensity());
      Serial.print("\t\t");
      Serial.print(led[i].getDarker());
      Serial.print("\t");
      Serial.print(led[i].getSpeedControlDuration());
      Serial.print("\t\t");
      Serial.println(led[i].getSpeedControlCounter());
    }
  Serial.println();
  Serial.print("loop duration / ms:\t");
  Serial.println(loopDuration);
  Serial.print("cycle time / ms:\t");
  Serial.println(cycleTime);
  Serial.println();
}

void LightSnake::clearAllLEDs()
{
  for (uint8_t i = 0; i < NUMBER_OF_LEDS; i++)
    {
      pwm.setPWM(i, 0, 0);
    }
  delay(DELAY_TEST);
}

int8_t LightSnake::getNumber()
{
  byte incomingNumber = 'g';
  int8_t number = -2;

  Serial.println();
  Serial.println("Enter a number");

  do
    {
      while (Serial.available() <= 0);
      incomingNumber = Serial.read();

      switch (incomingNumber)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5': 
        case '6': 
        case '7':
        case '8':
        case '9':
          number = incomingNumber - ASCII_OFFSET;
          break;
        case 'a':
        case 'A':
          number = 10;
          break;
        case 'b':
        case 'B':
          number = 11;
          break;
        case 'c':
        case 'C':
          number = 12;
          break;
        case 'd': 
        case 'D':
          number = 13;
          break;
        case 'e':
        case 'E':
          number = 14;
          break;
        case 'f':
        case 'F':
          number = 15;
          break;
        case 'x':
        case 'X':
          number = -1;
        default:
          number = -2;
          break;
        }
    }while (number <= -2);
    
  Serial.println(number);
  return number;
}
  
void LightSnake::getLEDNumber()
{
  int8_t number = -1;
  bool numberInCorrectRange = false;

  clearAllLEDs();
  
  do
    {
      number = getNumber();
      numberInCorrectRange =  ((number >= 0) && (number < NUMBER_OF_LEDS));
      if (numberInCorrectRange)
        {
          Serial.println(number);
          testLED(number);
        }
    }while (numberInCorrectRange);
}

void LightSnake::testLED(uint8_t address)
{
  Serial.print("Test of LED ");
  Serial.println(address);
  pwm.setPWM(address, 0, FULL_INTENSITY);
  delay(DELAY_TEST);
  pwm.setPWM(address,0 ,0);
  delay(DELAY_TEST);
}

void LightSnake::testAllLEDs()
{
  for (uint8_t i = 0; i < NUMBER_OF_LEDS; i++)
    {
      testLED(i);
    }
}

void LightSnake::invertOutputOfLoopDuration()
{
  outputOfLoopDuration = !outputOfLoopDuration;
  if (outputOfLoopDuration)
    {
      Serial.println("Output of Loop Duration enabled.");
    }
  else
    {
      Serial.println("Output of Loop Duration disabled.");
    }
}

void LightSnake::changeLoopDuration()
{
  int8_t newCycleTime = getNumber();
  if (newCycleTime >= 0)
    {
      cycleTime = (unsigned long)newCycleTime * 5;
    }
}

void LightSnake::setIndex()
{
  int8_t newIndex = getNumber();
  if ((newIndex >= 0) && (newIndex < NUMBER_OF_LEDS))
    {
      for (uint8_t i = 0; i < NUMBER_OF_LEDS; i++)
          {
            led[i].setProgmemIndex(newIndex);
          }
    }
}
