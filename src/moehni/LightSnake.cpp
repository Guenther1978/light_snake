#include "LightSnake.hpp"

void LightSnake::setup()
{
  pwm.begin();
  pwm.setPWMFreq(1600);

  for (uint8_t i = 0; i < NUMBER_OF_LEDS; i ++)
  {
    led[i].setNumber(i);
  }

  old_millis = millis();
  randomSeed(analogRead(0));
  Serial.begin(9600);
  Serial.print("Setup completed");
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
  while (millis() < (old_millis + DELAY_TIME));
  old_millis = millis();
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
}

void LightSnake::clearAllLEDs()
{
  for (uint8_t i = 0; i < NUMBER_OF_LEDS; i++)
    {
      pwm.setPWM(i, 0, 0);
    }
  delay(DELAY_TEST);
}

void LightSnake::getLEDNumber()
{
  byte incomingNumber = 'g';
  uint8_t number = 14;

  clearAllLEDs();
  Serial.println();
  Serial.println("Enter a number");
  
  do
    {
      while (!Serial.available());
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
          number = incomingNumber - 48;
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
        default:
          break;
        }
      Serial.println(number);
      testLED(number);
    }while ((incomingNumber != 'x') && (incomingNumber != 'X'));
}

void LightSnake::testLED(uint8_t address)
{
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
