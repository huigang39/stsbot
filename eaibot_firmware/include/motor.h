/**
 * @file motor.h
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

  /// @brief This class allows to control a DC motor by enabling it and setting its speed. The
  /// involved pins are expected to be connected to a full-bridge motor driver module, such as the
  /// L298N.
  class Motor
  {
  public:
    /// @brief Constructs a new Motor object.
    ///
    /// @param enable_gpio_pin Motor enable GPIO pin.
    /// @param forward_gpio_pin Motor forward GPIO pin.
    /// @param backward_gpio_pin Motor backward GPIO pin.
    Motor(int enable_gpio_pin, int forward_gpio_pin, int backward_gpio_pin)
        : enable_gpio_pin_(enable_gpio_pin),
          forward_gpio_pin_(forward_gpio_pin),
          backward_gpio_pin_(backward_gpio_pin) {}

    /// @brief Sets the motor state.
    ///
    /// @param enabled Motor state.
    void set_state(bool enabled);

    /// @brief Sets the motor speed.
    ///
    /// @param speed Motor speed value.
    void set_speed(int speed);

  private:
    /// Minimum speed value (negative speeds are considered as positive backward speeds).
    static constexpr int kMinSpeed{0};

    /// Maximum speed value.
    static constexpr int kMaxSpeed{255};

    /// Motor enable GPIO pin.
    int enable_gpio_pin_;

    /// Motor forward GPIO pin.
    int forward_gpio_pin_;

    /// Motor backward GPIO pin.
    int backward_gpio_pin_;
  };

} // namespace eaibot
