//
// Created by xuzhekai on 18/11/23.
//

#ifndef UNITREEMOTORSDK_M80106_PREPROGRAMMED_H
#define UNITREEMOTORSDK_M80106_PREPROGRAMMED_H

#include "serialPort/SerialPort.h"
#include <unistd.h>
#include <chrono>
#include <fstream>

/*Global variable*/
static double K_I = 0.0011; // 0.01 / 1000;
static double max_I = 5000;
static double K_P = 0.015; //0.01;
static double Tor_ff = 0.092;

bool PID_control(MotorCmd& cmd, MotorData& data, SerialPort& serial_port);



#endif //UNITREEMOTORSDK_M80106_PREPROGRAMMED_H
