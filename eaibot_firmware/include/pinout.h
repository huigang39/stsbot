/**
 * @file pinout.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <stdint.h>

namespace eaibot
{
    struct Pinout
    {
        static constexpr int8_t kLeftEncoderPinA{3};
        static constexpr int8_t kLeftEncoderPinB{2};

        static constexpr int8_t kRightEncoderPinA{18};
        static constexpr int8_t kRightEncoderPinB{19};

        static constexpr int8_t kLeftMotorEnablePin{12};
        static constexpr int8_t kLeftMotorForwardPin{7};
        static constexpr int8_t kLeftMotorBackwardPin{6};

        static constexpr int8_t kRightMotorEnablePin{13};
        static constexpr int8_t kRightMotorForwardPin{10};
        static constexpr int8_t kRightMotorBackwardPin{9};
    };
}