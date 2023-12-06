/**
 * @file encoder.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <stdint.h>
#include "pcint.h"

namespace eaibot
{
    class Encoder
    {
    public:
        Encoder(uint8_t pinA, uint8_t pinB) : pinA(pinA), pinB(pinB), count(0){};

        void init();

        int32_t read();

        void reset();

    private:
        static constexpr int8_t kTicksDelta[] = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0};

        static constexpr uint8_t kInstancesMax = 2;

        static const PCInt::InterruptCallback kCallbacks[kInstancesMax];

        static void callback0();
        static void callback1();

        void callback();

        uint8_t pinA;
        uint8_t pinB;

        int32_t count;
    };
}