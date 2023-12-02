/**
 * @file motor.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <motor.h>

Motor::Motor(bool isMotor1Attached, uint8_t pin1, uint8_t pin2, bool isMotor2Attached, uint8_t pin3, uint8_t pin4) : m_motorPin{{pin1, pin2}, {pin3, pin4}}, m_motorAttached{isMotor1Attached, isMotor2Attached}
{
    if (isMotor1Attached)
    {
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
    }
    if (isMotor2Attached)
    {
        pinMode(pin3, OUTPUT);
        pinMode(pin4, OUTPUT);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
    }
}

void Motor::attachMotor(uint8_t id, uint8_t pina, uint8_t pinb)
{
    if (id > 3)
    {
        return;
    }
    m_motorAttached[id] = true;
    pinMode(pina, OUTPUT);
    pinMode(pinb, OUTPUT);
    digitalWrite(pina, LOW);
    digitalWrite(pinb, LOW);
}

void Motor::stopMotor(uint8_t id)
{
    if (id > 3)
    {
        return;
    }
    if (m_motorAttached[id])
    {
        digitalWrite(getMotorPin(id)[0], LOW);
        digitalWrite(getMotorPin(id)[1], LOW);
    }
}

void Motor::updateMotorSpeed(uint8_t id, uint16_t pwmValue)
{
    if (id > 3)
    {
        return;
    }
    if (m_motorAttached[id])
    {
        analogWrite(getMotorPin(id)[0], pwmValue);
        analogWrite(getMotorPin(id)[1], pwmValue);
    }
}

uint8_t *Motor::getMotorPin(uint8_t id)
{
    if (id > 3)
    {
        return nullptr;
    }
    return m_motorPin[id];
}