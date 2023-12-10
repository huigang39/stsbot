/**
 * @file pid.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <stdint.h>

namespace eaibot
{
    class PID
    {
    private:
        uint8_t kp_;
        uint8_t ki_;
        uint8_t kd_;
        uint8_t ko_;
        uint8_t outputMin_;
        uint8_t outputMax_;
        bool enabled_ = false;
        uint8_t setpoint_ = 0;
        uint8_t intergralTerm_ = 0;
        uint32_t lastEncoderCount_ = 0;
        uint8_t lastInput_ = 0;
        uint32_t lastOutput_ = 0;

    public:
        PID(uint8_t kp, uint8_t ki, uint8_t kd, uint8_t ko, uint8_t outputMin, uint8_t outputMax) : kp_(kp), ki_(ki), kd_(kd), ko_(ko), outputMin_(outputMin), outputMax_(outputMax) {}
        void enable(bool enabled);
        void reset(int32_t encoderCount);
        void compute(int32_t encoderCount, int32_t &computedOutput);
        void setSetpoint(uint8_t setpoint);
        void setTunings(uint8_t kp, uint8_t ki, uint8_t kd, uint8_t ko);
    };
}