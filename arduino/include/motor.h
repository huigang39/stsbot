/**
 * @file motor.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <Arduino.h>

class Motor
{
private:
    uint8_t m_motorPin[2][2]{{0, 0}, {0, 0}};
    bool m_motorAttached[2]{false, false};

public:
    Motor() = default;
    Motor(bool id1, uint8_t pin1, uint8_t pin2, bool id2, uint8_t pin3, uint8_t pin4);
    ~Motor() = default;
    void attachMotor(uint8_t id, uint8_t pina, uint8_t pinb);
    void stopMotor(uint8_t id = -1);
    void updateMotorSpeed(uint8_t id, uint16_t pwmValue);
    uint8_t *getMotorPin(uint8_t id);
};

#endif