//
// Created by xuzhekai on 24/11/23.
//
#include "serialPort/SerialPort.h"
#include <unistd.h>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;



int main(int argc, char ** argv){
    std::ofstream myfile("../data/forward.csv");


    SerialPort  serial("/dev/ttyUSB0");
    MotorCmd    cmd;
    MotorData   data;
    cmd.motorType = MotorType::GO_M8010_6;
    cmd.id    = 0;
    cmd.mode  = 1;
    cmd.K_P   = 0.0;
    cmd.K_W   = 0.0;
    cmd.Pos   = 0.0;
//      cmd.W     =atof(argv[1]);
    cmd.W     =0.0;
    cmd.T     = 0.0;
    serial.sendRecv(&cmd,&data);

    for(float i = 0.0; i < 2.0;i+= 0.01){
        cmd.T = i;

        serial.sendRecv(&cmd,&data);

        usleep(5000000);
        serial.sendRecv(&cmd,&data);
        myfile << cmd.T << ", " << data.W << ", \n";
        cout  << cmd.T << ", " << data.W << ", \n";

        
//        cout << cmd.T << endl;

    }
myfile.close();
//


    return 0;
}