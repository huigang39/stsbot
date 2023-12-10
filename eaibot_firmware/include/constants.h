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

namespace name
{
    struct Constants
    {
        static constexpr int32_t kBaudRate{57600};
        static constexpr int32_t kAutoStopWindow{3000};
        static constexpr int8_t kPwmMin{0};
        static constexpr int8_t kPwmMax{255};

        static constexpr int8_t kPidRate{30};
        static constexpr int64_t kPidKp{0.5};
    };
}
