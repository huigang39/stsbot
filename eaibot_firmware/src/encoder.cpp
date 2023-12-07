/**
 * @file encoder.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "encoder.h"
#include "Arduino.h"

namespace eaibot
{
    constexpr int8_t Encoder::kTicksDelta[];

    Encoder *Encoder::instances[kInstancesMax] = {nullptr, nullptr};
    void Encoder::callback0()
    {
        if (Encoder::instances[0] != nullptr)
        {
            Encoder::instances[0]->callback();
        }
    }

    void Encoder::callback1()
    {
        if (Encoder::instances[1] != nullptr)
        {
            Encoder::instances[1]->callback();
        }
    }
}
