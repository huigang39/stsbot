/**
 * @file bot.h
 * @author Huigang Wang (huigang39@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __BOT_H__
#define __BOT_H__

// mico-ROS
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rclc_parameter/rclc_parameter.h>

// ROS2 messag
class Bot
{
private:
    /* data */
public:
    Bot(/* args */);
    ~Bot() = default;
};

#endif