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
        Encoder(uint8_t pinA, uint8_t pinB) : pinA_(pinA), pinB_(pinB){};
        void init();
        int32_t read();
        void reset();

    private:
        static constexpr int8_t kTicksDelta_[] = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0};
        static constexpr uint8_t kInstancesMax_ = 2;
        static const PCInt::InterruptCallback kCallbacks_[kInstancesMax_];

        static void callback0();
        static void callback1();

        void callback();

        static Encoder *instances_[kInstancesMax_];
        static int32_t instanceCount_;

        uint8_t pinA_;
        uint8_t pinB_;

        uint8_t state_ = {0x00};
        volatile int32_t count_ = {0L};
    };
}