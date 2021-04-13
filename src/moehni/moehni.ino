#include "LightSnake.hpp"


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
unsigned long old_millis;

Led led[NUMBER_OF_LEDS];
SpeedControl speedControl[NUMBER_OF_LEDS];

void setup()
{
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(1600);
  randomSeed(analogRead(0));
  Serial.println("Setup completed");
  old_millis = millis();
  for (uint8_t i = 0; i < NUMBER_OF_LEDS; i ++)
  {
    led[i].setNumber(i);
  }
}
 
void loop()
{
  for (uint8_t i = 0; i < NUMBER_OF_LEDS; i ++)
  {
    speedControl[i].count();
    if (speedControl[i].getTrigger())
    {
      led[i].changePointer();
      led[i].pointer2int();
      if (led[i].getDarkerHasChanged())
      {
        speedControl[i].setDuration(random(1,5));
      }
      pwm.setPWM(led[i].getNumber(), 0, led[i].getIntensity());  
    }
  }
  while (millis() < old_millis + 1000);
}
