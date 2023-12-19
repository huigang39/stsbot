/**
 * @file encoder.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "encoder.h"

#include <stdint.h>

#include "Arduino.h"
#include "pcint.h"

namespace eaibot
{

  constexpr int8_t Encoder::kTicksDelta[];

  const PCInt::InterruptCallback Encoder::kCallbacks[kInstancesMax] = {callback_0, callback_1};

  void Encoder::callback_0()
  {
    if (Encoder::instances_[0] != nullptr)
    {
      Encoder::instances_[0]->callback();
    }
  }

  void Encoder::callback_1()
  {
    if (Encoder::instances_[1] != nullptr)
    {
      Encoder::instances_[1]->callback();
    }
  }

  Encoder *Encoder::instances_[kInstancesMax] = {nullptr, nullptr};
  int Encoder::instance_count_ = 0;

  void Encoder::init()
  {
    // The current implementation only supports two instances of this class to be constructed. This
    // prevents reaching a buffer overflow.
    if (instance_count_ == kInstancesMax)
    {
      return;
    }

    pinMode(a_gpio_pin_, INPUT_PULLUP);
    pinMode(b_gpio_pin_, INPUT_PULLUP);
    eaibot::PCInt::attach_interrupt(a_gpio_pin_, kCallbacks[instance_count_]);
    eaibot::PCInt::attach_interrupt(b_gpio_pin_, kCallbacks[instance_count_]);

    instances_[instance_count_] = this;
    instance_count_++;
  }

  long Encoder::read() { return count_; }

  void Encoder::reset() { count_ = 0L; }

  void Encoder::callback()
  {
    // Read the current channels state into the lowest 2 bits of the encoder state.
    state_ <<= 2;
    state_ |= (digitalRead(b_gpio_pin_) << 1) | digitalRead(a_gpio_pin_);

    // Update the encoder count accordingly.
    count_ += kTicksDelta[(state_ & 0x0F)];
  }

} // namespace eaibot
