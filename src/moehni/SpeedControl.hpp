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
public:
  /**@return the value of the counter*/
  uint8_t getCounter();

  /**@param counter*/
  void setCounter(uint8_t);

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

  /**
   * @brief decreases _counter
   *
   * The method decreases the counter, if the counter
   * has the value zero true is returned.
   */
  bool count();
};

#endif
