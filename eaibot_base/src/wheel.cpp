/**
 * @file wheel.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "eaibot_base/wheel.h"

#include <cmath>

namespace eaibot_base
{

    void Wheel::Setup(const std::string &wheel_name, int ticks_per_rev)
    {
        name_ = wheel_name;
        rads_per_tick_ = (2 * M_PI) / ticks_per_rev;
    }

    double Wheel::Angle() { return enc_ * rads_per_tick_; }

}
