/**
 * @file main.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "app.h"

/// @brief Application entry point.
///
/// @return Execution final status (never reached).
int main(void)
{
  // Application configuration.
  eaibot::App::setup();

  // Application main run loop.
  while (1)
  {
    eaibot::App::loop();
  }

  return 0;
}
