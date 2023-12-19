/**
 * @file motor.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "motor.h"

#include "Arduino.h"

namespace eaibot
{

  void Motor::set_state(bool enabled)
  {
    if (enabled)
    {
      digitalWrite(enable_gpio_pin_, HIGH);
    }
    else
    {
      digitalWrite(enable_gpio_pin_, LOW);
    }
  }

  void Motor::set_speed(int speed)
  {
    bool forward = true;

    if (speed < kMinSpeed)
    {
      speed = -speed;
      forward = false;
    }
    if (speed > kMaxSpeed)
    {
      speed = kMaxSpeed;
    }

    // The motor speed is controlled by sending a PWM wave to the corresponding pin.
    if (forward)
    {
      analogWrite(forward_gpio_pin_, speed);
      analogWrite(backward_gpio_pin_, 0);
    }
    else
    {
      analogWrite(backward_gpio_pin_, speed);
      analogWrite(forward_gpio_pin_, 0);
    }
  }

} // namespace eaibot
