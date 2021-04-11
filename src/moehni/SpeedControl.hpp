#ifndef SPEED_CONTROL_H
#define SPEED_CONTROL_H

#include <Arduino.h>

class SpeedControl
{
private:
  uint8_t _number = 0;
  uint8_t _duration = 1;
  uint8_t _max_duration = 5;
  uint8_t _counter = 0;
  bool _trigger = false;
public:
  /**@return the number of the LED*/
  uint8_t getNumber();

  /**@param number*/
  void setNumber(uint8_t);

  /**@return duration of the LED*/
  uint8_t getDuration();

  /**@param duration
   *
   * The duration delays the true state
   * of _trigger.
   */
  void setDuration(uint8_t);

  /**@return true if _counter == 0*/
  bool getTrigger();

  /**
   * @brief decreases _counter
   *
   * The method is used to count down the _counter variable,
   * which delays the true state of the _trigger variable.
   */
  void count();
};

#endif
