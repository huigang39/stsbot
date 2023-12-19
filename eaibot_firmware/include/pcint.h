/**
 * @file pcint.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <stdint.h>

#include "Arduino.h"

namespace eaibot
{

  /// @brief This class provides a simple way to set and use Pin Change Interrupts.
  class PCInt
  {
  public:
    /// @brief Interrupt callback type.
    typedef void (*InterruptCallback)();

    /// @brief Attaches an interrupt callback.
    /// @note Only one callback per port is supported.
    ///
    /// @param pin Pin of interest.
    /// @param callback Callback function.
    static void attach_interrupt(uint8_t pin, InterruptCallback callback);

  private:
    /// Map between ports and Pin Change Mask registers.
    static constexpr volatile uint8_t *kPortToPCMask[]{&PCMSK0, &PCMSK1, &PCMSK2};
  };

} // namespace eaibot
