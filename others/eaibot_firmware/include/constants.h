/**
 * @file constants.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <stdint.h>

namespace eaibot
{
    struct Constants
    {
        static constexpr uint32_t kBaudRate{57600};
        static constexpr uint32_t kAutoStopWindow{3000};
        static constexpr uint8_t kPwmMin{0};
        static constexpr uint8_t kPwmMax{255};
        static constexpr uint8_t kPidRate{30};
        static constexpr double kPidPeriod{1000 / kPidRate};
        static constexpr uint8_t kPidKp{30};
        static constexpr uint8_t kPidKi{0};
        static constexpr uint8_t kPidKd{10};
        static constexpr uint8_t kPidKo{10};
    };
}
