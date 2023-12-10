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

namespace eaibot
{
    class Motor
    {
    private:
        uint8_t enableGpioPin_;
        uint8_t forwardGpioPin_;
        uint8_t backwardGpioPin_;

        static constexpr uint8_t kMinSpeed = 0;
        static constexpr uint8_t kMaxSpeed = 255;

    public:
        Motor(int enable_gpio_pin, int forward_gpio_pin, int backward_gpio_pin)
            : enableGpioPin_(enable_gpio_pin),
              forwardGpioPin_(forward_gpio_pin),
              backwardGpioPin_(backward_gpio_pin) {}

        void setState(bool enabled);
        void setSpeed(uint16_t speed);
    };
}
