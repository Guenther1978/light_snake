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
      Serial.println("New Intensity:");
      Serial.print(led[i].getNumber());
      Serial.print("\t");
      Serial.print(led[i].getIntensity());
      Serial.println();
      if (led[i].getDarkerHasChanged())
      {
        led[i].setSpeedControlDuration(random(1, DURATION_MAX));
        Serial.print("\t");
        Serial.println("New Duration:");
        Serial.print(led[i].getNumber());
        Serial.print("\t");
        Serial.print(led[i].getSpeedControlDuration());
        Serial.println();
      }
      pwm.setPWM(led[i].getNumber(), 0, led[i].getIntensity());
    }
  }
  while (millis() < (old_millis + DELAY_TIME));
  old_millis = millis();
}
