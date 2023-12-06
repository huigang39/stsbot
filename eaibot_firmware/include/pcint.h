/**
 * @file pcint.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "Arduino.h"

namespace eaibot
{
    class PCInt
    {
    private:
        static constexpr volatile uint8_t *kPortToPCMask[] = {&PCMSK0, &PCMSK1, &PCMSK2};

    public:
        typedef void (*InterruptCallback)();
        static void attachInterrupt(uint8_t pin, InterruptCallback callback);
    };
}
