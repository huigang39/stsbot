/**
 * @file encoder.h
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

#include "pcint.h"

namespace eaibot {

/// @brief This class allows to use a quadrature encoder by configuring it and then getting its
/// ticks count value.
/// @note The current implementation only supports two instances of this class to be constructed.
class Encoder {
 public:
  /// @brief Constructs a new Encoder object.
  ///
  /// @param a_gpio_pin Encoder channel A GPIO pin.
  /// @param b_gpio_pin Encoder channel B GPIO pin.
  Encoder(int a_gpio_pin, int b_gpio_pin) : a_gpio_pin_(a_gpio_pin), b_gpio_pin_(b_gpio_pin) {}

  /// @brief Initializes the encoder.
  void init();

  /// @brief Returns the ticks count value.
  ///
  /// @return Ticks count value.
  long read();

  /// @brief Sets the ticks count value to zero.
  void reset();

 private:
  /// Ticks delta lookup table. Its content is defined as follows:
  ///   +--------+-----+-----+--------+-----------+
  ///   | Number | Old | New | Binary | Direction |
  ///   |        | A B | A B |        |           |
  ///   +--------+-----+-----+--------+-----------+
  ///   |    0   | 0 0 | 0 0 |  0000  |     0     |
  ///   |    1   | 0 0 | 0 1 |  0001  |    +1     |
  ///   |    2   | 0 0 | 1 0 |  0010  |    -1     |
  ///   |    3   | 0 0 | 1 1 |  0011  |     0     |
  ///   |    4   | 0 1 | 0 0 |  0100  |    -1     |
  ///   |    5   | 0 1 | 0 1 |  0101  |     0     |
  ///   |    6   | 0 1 | 1 0 |  0110  |     0     |
  ///   |    7   | 0 1 | 1 1 |  0111  |    +1     |
  ///   |    8   | 1 0 | 0 0 |  1000  |    +1     |
  ///   |    9   | 1 0 | 0 1 |  1001  |     0     |
  ///   |   10   | 1 0 | 1 0 |  1010  |     0     |
  ///   |   11   | 1 0 | 1 1 |  1011  |    -1     |
  ///   |   12   | 1 1 | 0 0 |  1100  |     0     |
  ///   |   13   | 1 1 | 0 1 |  1101  |    -1     |
  ///   |   14   | 1 1 | 1 0 |  1110  |    +1     |
  ///   |   15   | 1 1 | 1 1 |  1111  |     0     |
  ///   +--------+-----+-----+--------+-----------+
  static constexpr int8_t kTicksDelta[]{0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0};

  /// Maximum number of instances of this class that can be instantiated.
  static constexpr int kInstancesMax{2};

  /// Static wrappers that redirect to instance callback methods.
  static const PCInt::InterruptCallback kCallbacks[kInstancesMax];

  /// Static wrapper that redirects to the first instance callback method.
  static void callback_0();

  /// Static wrapper that redirects to the second instance callback method.
  static void callback_1();

  /// Channels GPIO interrupt callback.
  void callback();

  /// Holds references to the constructed Encoder instances.
  static Encoder* instances_[kInstancesMax];

  /// Number of constructed Encoder instances.
  static int instance_count_;

  /// Channel A GPIO pin.
  int a_gpio_pin_;

  /// Channel B GPIO pin.
  int b_gpio_pin_;

  /// Encoder state. It contains both the current and previous channels state readings:
  ///   +------+-----+-----+-----+-----+-----+-----+-----+-----+
  ///   | Bits |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
  ///   +------+-----+-----+-----+-----+-----+-----+-----+-----+
  ///   |      |  x  |  x  |  x  |  x  | PREVIOUS  |  CURRENT  |
  ///   +------+-----+-----+-----+-----+-----+-----+-----+-----+
  uint8_t state_{0x00};

  /// Ticks count.
  volatile long count_{0L};
};

}  // namespace eaibot
