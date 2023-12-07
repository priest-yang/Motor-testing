////
//// Created by xuzhekai on 20/11/23.
////
//#include "serialPort/SerialPort.h"
//#include <unistd.h>
//using std::cout;
//using std::endl;
//
//
//
//int main(int argc, char ** argv){
//
//    SerialPort  serial("/dev/ttyUSB0");
//    MotorCmd    cmd;
//    MotorData   data;
//
//    cmd.motorType = MotorType::GO_M8010_6;
//    cmd.id    = 0;
//    cmd.mode  = 1;
//    cmd.K_P   = 0.0;
//    cmd.K_W   = 0.1;
//    cmd.Pos   = 0.0;
////      cmd.W     =atof(argv[1]);
//    cmd.W     =20;
//    cmd.T     = 0.0;
//    serial.sendRecv(&cmd,&data);
//
//    cmd.id    = 1;
//    cmd.mode  = 1;
//    cmd.K_P   = 0.0;
//    cmd.K_W   = 0.0;
//    cmd.Pos   = 0.0;
////      cmd.W     =atof(argv[1]);
//    cmd.W     =0.0;
//    cmd.T     = 0.0;
//    serial.sendRecv(&cmd,&data);
//    cout << cmd.W << endl;
//
//    return 0;
//}

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
//    std::ofstream myfile("../data/forward.csv");
    cmd.id = 1;
    serial.sendRecv(&cmd,&data);
    cmd.id = 0;
    for(float i = 0.08; i < 0.15;i+= 0.001){

        cmd.T = i;

        serial.sendRecv(&cmd,&data);

        usleep(1000000);
        serial.sendRecv(&cmd,&data);
        myfile << cmd.T << ", " << data.W << ", \n\r";
        cout  << cmd.T << ", " << data.W << ", \n";
        usleep(2000000);
        serial.sendRecv(&cmd,&data);
        myfile << cmd.T << ", " << data.W << ", \n\r";
        cout  << cmd.T << ", " << data.W << ", \n";

        cmd.id = 0;
        cmd.T = 0;
        serial.sendRecv(&cmd,&data);
        usleep(1000000);
//        myfile.close();

//        cout << cmd.T << endl;

    }
    myfile.close();
//


    return 0;
}