/**
 * @file motor.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <stdint.h>

namespace stsbot
{
    class Motor
    {
    private:
        uint8_t enableGpioPin;
        uint8_t forwardGpioPin;
        uint8_t backwardGpioPin;

        static constexpr uint8_t kMinSpeed = 0;
        static constexpr uint8_t kMaxSpeed = 255;

    public:
        Motor(int enable_gpio_pin, int forward_gpio_pin, int backward_gpio_pin)
            : enableGpioPin(enable_gpio_pin),
              forwardGpioPin(forward_gpio_pin),
              backwardGpioPin(backward_gpio_pin) {}

        void setState(bool enabled);
        void setSpeed(uint16_t speed);
    };
}
