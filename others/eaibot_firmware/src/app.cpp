/**
 * @file app.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "app.h"

#include "Arduino.h"
#include "constants.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"
#include "pinout.h"
#include "commands.h"

uint32_t nextPID = eaibot::Constants::kPidPeriod;
uint32_t lastMotorCommand = eaibot::Constants::kAutoStopWindow;

int8_t arg = 0;
int8_t index = 0;

char chr;
char cmd;

char argv1[16];
char argv2[16];

int32_t arg1;
int32_t arg2;

namespace eaibot
{
    Motor App::leftMotor_(Pinout::kLeftMotorEnablePin, Pinout::kLeftMotorForwardPin, Pinout::kLeftMotorBackwardPin);

    Motor App::rightMotor_(Pinout::kRightMotorEnablePin, Pinout::kRightMotorForwardPin, Pinout::kRightMotorBackwardPin);

    Encoder App::leftEncoder_(Pinout::kLeftEncoderPinA, Pinout::kLeftEncoderPinB);

    Encoder App::rightEncoder_(Pinout::kRightEncoderPinA, Pinout::kRightEncoderPinB);

    PID App::leftPID_(Constants::kPidKp, Constants::kPidKi, Constants::kPidKd, Constants::kPidKo, Constants::kPwmMin, Constants::kPwmMax);

    PID App::rightPID_(Constants::kPidKp, Constants::kPidKi, Constants::kPidKd, Constants::kPidKo, Constants::kPwmMin, Constants::kPwmMax);

    void App::setup()
    {
        Serial.begin(Constants::kBaudRate);

        leftMotor_.setState(true);
        rightMotor_.setState(true);

        leftEncoder_.init();
        rightEncoder_.init();

        leftPID_.reset(leftEncoder_.read());
        rightPID_.reset(rightEncoder_.read());
    }

    void App::loop()
    {
        while (Serial.available() > 0)
        {
            chr = Serial.read();

            if (chr == 13)
            {
                if (arg == 1)
                {
                    argv1[index] = 0;
                }
                else if (arg == 2)
                {
                    argv2[index] = 0;
                }
                runCommand();
                resetCommand();
            }
            else if (chr == ' ')
            {
                if (arg == 0)
                {
                    arg = 1;
                }
                else if (arg == 1)
                {
                    argv1[index] = 0;
                    arg = 2;
                    index = 0;
                }
                continue;
            }
            else
            {
                if (arg == 0)
                {
                    cmd = chr;
                }
                else if (arg == 1)
                {
                    argv1[index++] = chr;
                }
                else if (arg == 2)
                {
                    argv2[index++] = chr;
                }
            }
        }

        if (millis() > nextPID)
        {
            int32_t leftMotorSpeed = 0;
            int32_t rightMotorSpeed = 0;

            leftPID_.compute(leftEncoder_.read(), leftMotorSpeed);
            rightPID_.compute(rightEncoder_.read(), rightMotorSpeed);

            leftMotor_.setSpeed(leftMotorSpeed);
            rightMotor_.setSpeed(rightMotorSpeed);

            nextPID += Constants::kPidPeriod;
        }

        if ((millis() - lastMotorCommand) > Constants::kAutoStopWindow)
        {
            leftMotor_.setSpeed(0);
            rightMotor_.setSpeed(0);
            leftPID_.enable(false);
            rightPID_.enable(false);
        }

        if (serialEventRun)
        {
            serialEventRun();
        }
    }

    void App::resetCommand()
    {
        cmd = 0;
        memset(argv1, 0, sizeof(argv1));
        memset(argv2, 0, sizeof(argv2));
        arg1 = 0;
        arg2 = 0;
        arg = 0;
        index = 0;
    }

    void App::runCommand()
    {
        int i = 0;
        char *p = argv1;
        char *str;
        int8_t pidArgs[4];
        arg1 = atoi(argv1);
        arg2 = atoi(argv2);

        switch (cmd)
        {
        case GET_BAUD_RATE:
            Serial.println(Constants::kBaudRate);
            break;
        case ANALOG_READ:
            Serial.println(analogRead(arg1));
            break;
        case DIGITAL_READ:
            Serial.println(digitalRead(arg1));
            break;
        case ANALOG_WRITE:
            analogWrite(arg1, arg2);
            Serial.println("OK");
            break;
        case DIGITAL_WRITE:
            if (arg2 == 0)
            {
                digitalWrite(arg1, LOW);
                Serial.println("OK");
            }
            else if (arg2 == 1)
            {
                digitalWrite(arg1, HIGH);
                Serial.println("OK");
            }
            else
            {
                Serial.println("ERROR");
            }
            break;
        case PIN_MODE:
            if (arg2 == 0)
            {
                pinMode(arg1, INPUT);
            }
            else if (arg2 == 1)
            {
                pinMode(arg1, OUTPUT);
            }
            Serial.println("OK");
            break;
        case READ_ENCODERS:
            Serial.print(leftEncoder_.read());
            Serial.print(" ");
            Serial.println(rightEncoder_.read());
            break;
        case RESET_ENCODERS:
            leftEncoder_.reset();
            rightEncoder_.reset();
            leftPID_.reset(leftEncoder_.read());
            leftPID_.reset(rightEncoder_.read());
            Serial.println("OK");
            break;
        case MOTOR_SPEEDS:
            lastMotorCommand = millis();
            if (arg1 == 0 && arg2 == 0)
            {
                leftMotor_.setSpeed(0);
                rightMotor_.setSpeed(0);

                leftPID_.reset(leftEncoder_.read());
                rightPID_.reset(rightEncoder_.read());

                leftPID_.enable(false);
                rightPID_.enable(false);
            }
            else
            {
                leftPID_.enable(true);
                rightPID_.enable(true);
            }

            leftPID_.setSetpoint(arg1 / Constants::kPidRate);
            rightPID_.setSetpoint(arg2 / Constants::kPidRate);

            Serial.println("OK");
            break;
        case MOTOR_RAW_PWM:
            lastMotorCommand = millis();
            leftPID_.reset(leftEncoder_.read());
            rightPID_.reset(rightEncoder_.read());
            leftPID_.enable(false);
            rightPID_.enable(false);
            leftMotor_.setSpeed(arg1);
            rightMotor_.setSpeed(arg2);
            Serial.println("OK");
            break;
        case UPDATE_PID:
            while ((str = strtok_r(p, ":", &p)) != NULL)
            {
                pidArgs[i++] = atoi(str);
            }
            leftPID_.setTunings(pidArgs[0], pidArgs[1], pidArgs[2], pidArgs[3]);
            rightPID_.setTunings(pidArgs[0], pidArgs[1], pidArgs[2], pidArgs[3]);
            Serial.print("PID Updated");
            Serial.print(pidArgs[0]);
            Serial.print(" ");
            Serial.print(pidArgs[1]);
            Serial.print(" ");
            Serial.print(pidArgs[2]);
            Serial.print(" ");
            Serial.println(pidArgs[3]);
            break;
        default:
            Serial.println("Invalid Command");
            break;
        }
    }
}