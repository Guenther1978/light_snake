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
      if (Serial.read() == 'd')
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
              Serial.print(led[i].getSpeedControlCounter());
              Serial.println();
            }
        }
    }
}
