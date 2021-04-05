#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Led.hpp"
#include "SpeedControl.hpp"
/*
#define INTENSITY_MIN 100
#define INTENSITY_MAX 4095
#define DURATION_MIN 1
#define DURATION_MAX 4
*/
#define NUMBER_OF_LEDS 14

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
      Serial.println(led[i].getNumber());
      Serial.println(led[i].getIntensity());
      Serial.println();
      pwm.setPWM(led[i].getNumber(), led[i].getIntensity(), 4096 - led[i].getIntensity());  
    }
  }
  while (millis() < old_millis + 1000);
}
