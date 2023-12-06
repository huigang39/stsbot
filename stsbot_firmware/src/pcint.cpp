/**
 * @file pcint.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "pcint.h"

static stsbot::PCInt::InterruptCallback g_callbacks[3] = {nullptr};

ISR(PCINT0_vect)
{
    if (g_callbacks[0] != nullptr)
    {
        g_callbacks[0]();
    }
}

ISR(PCINT1_vect)
{
    if (g_callbacks[1] != nullptr)
    {
        g_callbacks[1]();
    }
}

ISR(PCINT2_vect)
{
    if (g_callbacks[2] != nullptr)
    {
        g_callbacks[2]();
    }
}

namespace stsbot
{
    constexpr volatile uint8_t *PCInt::kPortToPCMask[];

    void PCInt::attachInterrupt(uint8_t pin, InterruptCallback callback)
    {
        uint8_t bit_mask = digitalPinToBitMask(pin);
        uint8_t port = digitalPinToPort(pin);

        if (port == NOT_A_PIN)
        {
            return;
        }

        port -= 2;

        *kPortToPCMask[port] |= bit_mask;

        PCICR |= (1 << port);

        g_callbacks[port] = callback;
    }
}