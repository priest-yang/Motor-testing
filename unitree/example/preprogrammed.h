//
// Created by xuzhekai on 18/11/23.
//

#ifndef UNITREEMOTORSDK_M80106_PREPROGRAMMED_H
#define UNITREEMOTORSDK_M80106_PREPROGRAMMED_H

#include "serialPort/SerialPort.h"
#include <unistd.h>

static double K_I = 0.01;
static double K_D = 0.01;
static double Tor_ff = 0.092;

bool PID_control(MotorCmd& cmd, MotorData& data, SerialPort& serial_port);



#endif //UNITREEMOTORSDK_M80106_PREPROGRAMMED_H
