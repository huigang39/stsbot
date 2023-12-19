/**
 * @file app.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "encoder.h"
#include "motor.h"
#include "pid.h"

namespace eaibot
{

  /// @brief This class wraps the MCU main application.
  class App
  {
  public:
    /// This class only contains static members.
    App() = delete;

    /// @brief Configures and sets the application up. Meant to be called once at startup.
    static void setup();

    /// @brief Application main run loop. Meant to be called continously.
    static void loop();

  private:
    /// Clears the current command parameters.
    // TODO(jballoffet): Move this method to a different module.
    static void reset_command();

    /// Runs a command.
    // TODO(jballoffet): Move this method to a different module.
    static void run_command();

    /// Motors (one per wheel).
    static Motor left_motor_;
    static Motor right_motor_;

    /// Encoders (one per wheel).
    static Encoder left_encoder_;
    static Encoder right_encoder_;

    /// PID controllers (one per wheel).
    static PID left_pid_controller_;
    static PID right_pid_controller_;
  };

} // namespace eaibot
