/**
 * @file pcint.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "pcint.h"

#include "Arduino.h"

static eaibot::PCInt::InterruptCallback g_callbacks[3] = {nullptr};

ISR(PCINT0_vect)
{
  if (g_callbacks[0] != nullptr)
  {
    g_callbacks[0]();
  }
}

ISR(PCINT1_vect)
{
  if (g_callbacks[1] != nullptr)
  {
    g_callbacks[1]();
  }
}

ISR(PCINT2_vect)
{
  if (g_callbacks[2] != nullptr)
  {
    g_callbacks[2]();
  }
}

namespace eaibot
{

  constexpr volatile uint8_t *PCInt::kPortToPCMask[];

  void PCInt::attach_interrupt(uint8_t pin, InterruptCallback callback)
  {
    uint8_t bit_mask = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);

    if (port == NOT_A_PORT)
    {
      return;
    }

    // Ports B, C and D values are 2, 3 and 4 correspondingly.
    port -= 2;

    // Set corresponding bit in the appropriate Pin Change Mask register.
    *(kPortToPCMask[port]) |= bit_mask;

    // Set corresponding bit in the Pin Change Interrupt Control register.
    PCICR |= 0x01 << port;

    // Set callback function.
    g_callbacks[port] = callback;
  }

} // namespace eaibot
