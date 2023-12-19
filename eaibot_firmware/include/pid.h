/**
 * @file pid.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

namespace eaibot
{

  /// @brief This class provides a simple PID controller implementation.
  class PID
  {
  public:
    /// @brief Constructs a new PID object.
    ///
    /// @param kp Tuning proportional gain.
    /// @param kd Tuning derivative gain.
    /// @param ki Tuning integral gain.
    /// @param ko Tuning output gain.
    /// @param output_min Output minimum limit.
    /// @param output_max Output maximum limit.
    PID(int kp, int kd, int ki, int ko, int output_min, int output_max)
        : kp_(kp),
          kd_(kd),
          ki_(ki),
          ko_(ko),
          output_min_(output_min),
          output_max_(output_max),
          enabled_(false) {}

    /// @brief Resets the PID controller.
    ///
    /// @param encoder_count Current encoder value.
    void reset(int encoder_count);

    /// @brief Enables the PID controller.
    ///
    /// @param enabled True to enable the PID, false otherwise.
    void enable(bool enabled);

    /// @brief Computes a new output.
    ///
    /// @param encoder_count Current encoder value.
    /// @param computed_output Computed output value.
    void compute(int encoder_count, int &computed_output);

    /// @brief Sets the setpoint.
    ///
    /// @param setpoint Desired setpoint value.
    void set_setpoint(int setpoint);

    /// @brief Sets the tuning gains.
    ///
    /// @param kp Tuning proportional gain.
    /// @param kd Tuning derivative gain.
    /// @param ki Tuning integral gain.
    /// @param ko Tuning output gain.
    void set_tunings(int kp, int kd, int ki, int ko);

  private:
    /// Tuning proportional gain.
    int kp_;
    /// Tuning derivative gain.
    int kd_;
    /// Tuning integral gain.
    int ki_;
    /// Tuning output gain.
    int ko_;

    /// Output minimum limit.
    int output_min_;
    /// Output maximum limit.
    int output_max_;

    /// True if the PID is enabled, false otherwise.
    bool enabled_;

    /// Setpoint value.
    int setpoint_;
    /// Accumulated integral term.
    int integral_term_;
    /// Last received encoder value.
    long last_encoder_count_;
    /// Last computed input value.
    int last_input_;
    /// Last computed output value.
    long last_output_;
  };

} // namespace eaibot
