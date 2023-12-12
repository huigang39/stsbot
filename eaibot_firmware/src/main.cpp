/**
 * @file main.cpp
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "app.h"

int main(void)
{
    eaibot::App::setup();

    while (1)
    {
        eaibot::App::loop();
    }

    return 0;
}