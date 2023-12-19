/**
 * @file pid.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "pid.h"

namespace eaibot
{

  // Note: see the following links for more information regarding this class implementation:
  //  - http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-initialization/
  //  - http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-derivative-kick/
  //  - http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-tuning-changes/

  void PID::reset(int encoder_count)
  {
    // Since we can assume that the PID is only turned on when going from stop to moving, we can init
    // everything on zero.
    setpoint_ = 0;
    integral_term_ = 0;
    last_encoder_count_ = encoder_count;
    last_input_ = 0;
    last_output_ = 0;
  }

  void PID::enable(bool enabled) { enabled_ = enabled; }

  void PID::compute(int encoder_count, int &computed_output)
  {
    if (!enabled_)
    {
      // Reset PID once to prevent startup spikes.
      if (last_input_ != 0)
      {
        reset(encoder_count);
      }
      return;
    }

    int input = encoder_count - last_encoder_count_;
    long error = setpoint_ - input;

    long output = (kp_ * error - kd_ * (input - last_input_) + integral_term_) / ko_;
    output += last_output_;

    // Accumulate integral term as long as output doesn't saturate.
    if (output >= output_max_)
    {
      output = output_max_;
    }
    else if (output <= output_min_)
    {
      output = output_min_;
    }
    else
    {
      integral_term_ += ki_ * error;
    }

    // Set the computed output accordingly.
    computed_output = output;

    // Store obtained values.
    last_encoder_count_ = encoder_count;
    last_input_ = input;
    last_output_ = output;
  }

  void PID::set_setpoint(int setpoint) { setpoint_ = setpoint; }

  void PID::set_tunings(int kp, int kd, int ki, int ko)
  {
    kp_ = kp;
    kd_ = kd;
    ki_ = ki;
    ko_ = ko;
  }

} // namespace eaibot
