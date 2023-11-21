//
// Created by xuzhekai on 20/11/23.
//
#include "serialPort/SerialPort.h"
#include <unistd.h>
using std::cout;
using std::endl;



int main(int argc, char ** argv){

    SerialPort  serial("/dev/ttyUSB0");
    MotorCmd    cmd;
    MotorData   data;

    cmd.motorType = MotorType::GO_M8010_6;
    cmd.id    = 0;
    cmd.mode  = 1;
    cmd.K_P   = 0.0;
    cmd.K_W   = 0.09;
    cmd.Pos   = 0.0;
      cmd.W     =atof(argv[1]);
//    cmd.W     =50;
    cmd.T     = 0.0;

    serial.sendRecv(&cmd,&data);
    cout << cmd.W << endl;

    return 0;
}