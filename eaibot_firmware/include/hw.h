/**
 * @file hw.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

namespace eaibot {

/// @brief Hardware configuration.
struct Hw {
  /// @brief Left encoder channel A pin. Connected to PD2 (digital pin 2).
  static constexpr int kLeftEncoderChannelAGpioPin{2};
  /// @brief Left encoder channel B pin. Connected to PD3 (digital pin 3).
  static constexpr int kLeftEncoderChannelBGpioPin{3};

  /// @brief Right encoder channel A pin. Connected to PC4 (digital pin 18, analog pin A4).
  static constexpr int kRightEncoderChannelAGpioPin{18};
  /// @brief Right encoder channel B pin. Connected to PC5 (digital pin 19, analog pin A5).
  static constexpr int kRightEncoderChannelBGpioPin{19};

  /// @brief Left motor driver backward pin. Connected to PD6 (digital pin 6).
  static constexpr int kLeftMotorBackwardGpioPin{6};
  /// @brief Left motor driver forward pin. Connected to PB2 (digital pin 10).
  static constexpr int kLeftMotorForwardGpioPin{10};
  /// @brief Left motor driver enable pin. Connected to PB5 (digital pin 13).
  /// @note The enable input of the L298N motor driver may be directly jumped to 5V if the board has
  /// a jumper to do so.
  static constexpr int kLeftMotorEnableGpioPin{13};

  /// @brief Right motor driver backward pin. Connected to PD5 (digital pin 5).
  static constexpr int kRightMotorBackwardGpioPin{5};
  /// @brief Right motor driver forward pin. Connected to PB1 (digital pin 9).
  static constexpr int kRightMotorForwardGpioPin{9};
  /// @brief Right motor driver enable pin. Connected to PB4 (digital pin 12).
  /// @note The enable input of the L298N motor driver may be directly jumped to 5V if the board has
  /// a jumper to do so.
  static constexpr int kRightMotorEnableGpioPin{12};
};

}  // namespace eaibot
