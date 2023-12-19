/**
 * @file pid.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "pid.h"

void eaibot::PID::enable(bool enabled)
{
    enabled_ = enabled;
}

void eaibot::PID::reset(int32_t encoderCount)
{
    setpoint_ = 0;
    intergralTerm_ = 0;
    lastEncoderCount_ = encoderCount;
    lastInput_ = 0;
    lastOutput_ = 0;
}

void eaibot::PID::compute(int32_t encoderCount, int32_t &computedOutput)
{
    if (!enabled_)
    {
        if (lastInput_ != 0)
        {
            reset(encoderCount);
        }
        return;
    }

    int32_t input = encoderCount - lastEncoderCount_;
    int32_t error = setpoint_ - input;
    int32_t output = (kp_ * error - kd_ * (input - lastInput_) + intergralTerm_) / ko_;

    output += lastOutput_;

    if (output >= outputMax_)
    {
        output = outputMax_;
    }
    else if (output <= outputMin_)
    {
        output = outputMin_;
    }
    else
    {
        intergralTerm_ += ki_ * error;
    }

    computedOutput = output;

    lastEncoderCount_ = encoderCount;
    lastInput_ = input;
    lastOutput_ = output;
}

void eaibot::PID::setSetpoint(uint8_t setpoint)
{
    setpoint_ = setpoint;
}

void eaibot::PID::setTunings(uint8_t kp, uint8_t ki, uint8_t kd, uint8_t ko)
{
    kp_ = kp;
    ki_ = ki;
    kd_ = kd;
    ko_ = ko;
}