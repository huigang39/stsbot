/**
 * @file motor.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Arduino.h"
#include "motor.h"

namespace eaibot
{
    void Motor::setState(bool enabled)
    {
        if (enabled)
        {
            digitalWrite(enableGpioPin, HIGH);
        }
        else
        {
            digitalWrite(enableGpioPin, LOW);
        }
    }

    void Motor::setSpeed(uint16_t speed)
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

        if (forward)
        {
            analogWrite(forwardGpioPin, speed);
            analogWrite(backwardGpioPin, 0);
        }
        else
        {
            analogWrite(forwardGpioPin, 0);
            analogWrite(backwardGpioPin, speed);
        }
    }
}