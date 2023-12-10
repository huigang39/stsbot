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
    constexpr int8_t Encoder::kTicksDelta_[];

    Encoder *Encoder::instances_[kInstancesMax_] = {nullptr, nullptr};

    int32_t Encoder::instanceCount_ = 0;

    void Encoder::callback0()
    {
        if (Encoder::instances_[0] != nullptr)
        {
            Encoder::instances_[0]->callback();
        }
    }

    void Encoder::callback1()
    {
        if (Encoder::instances_[1] != nullptr)
        {
            Encoder::instances_[1]->callback();
        }
    }

    void Encoder::init()
    {
        if (instanceCount_ == kInstancesMax_)
        {
            return;
        }
        pinMode(pinA_, INPUT_PULLUP);
        pinMode(pinB_, INPUT_PULLUP);

        eaibot::PCInt::attachInterrupt(pinA_, kCallbacks_[instanceCount_]);
        eaibot::PCInt::attachInterrupt(pinB_, kCallbacks_[instanceCount_]);

        instances_[instanceCount_] = this;
        instanceCount_++;
    }

    int32_t Encoder::read()
    {
        return count_;
    }

    void Encoder::reset()
    {
        count_ = 0;
    }

    void Encoder::callback()
    {
        state_ <<= 2;
        state_ |= (digitalRead(pinA_) << 1) | digitalRead(pinB_);
        count_ += kTicksDelta_[state_ & 0x0f];
    }
}
