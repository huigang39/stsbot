/**
 * @file app.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "pid.h"
#include "motor.h"
#include "encoder.h"

namespace eaibot
{
    class App
    {
    public:
        App() = delete;

        static void setup();
        static void loop();

    private:
        static void resetCommand();
        static void runCommand();

        static Motor leftMotor_;
        static Motor rightMotor_;

        static Encoder leftEncoder_;
        static Encoder rightEncoder_;

        static PID leftPID_;
        static PID rightPID_;
    };
}