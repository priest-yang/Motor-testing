//#include "serialPort/SerialPort.h"
//#include <unistd.h>
//
//int main() {
//
//  SerialPort  serial("/dev/ttyUSB0");
//  MotorCmd    cmd;
//  MotorData   data;
//
////  while(true) {
//    cmd.motorType = MotorType::GO_M8010_6;
//    cmd.id    = 0;
//    cmd.mode  = 0;
//    cmd.K_P   = 0.0;
//    cmd.K_W   = 0.00;
//    cmd.Pos   = 0.0;
//    cmd.W     = 0;
//    cmd.T     = 0.0;
//    serial.sendRecv(&cmd,&data);
//
//      cmd.motorType = MotorType::GO_M8010_6;
//      cmd.id    = 1;
//      cmd.mode  = 0;
//      cmd.K_P   = 0.0;
//      cmd.K_W   = 0.00;
//      cmd.Pos   = 0.0;
//      cmd.W     = 0;
//      cmd.T     = 0.0;
//      serial.sendRecv(&cmd,&data);
//
//    if(data.correct == true)
//    {
//      std::cout <<  std::endl;
//      std::cout <<  "motor.Pos: "    << data.Pos    << " rad" << std::endl;
//      std::cout <<  "motor.Temp: "   << data.Temp   << " ℃"  << std::endl;
//      std::cout <<  "motor.W: "      << data.W      << " rad/s"<<std::endl;
//      std::cout <<  "motor.T: "      << data.T      << " N.m" << std::endl;
//      std::cout <<  "motor.MError: " << data.MError <<  std::endl;
//      std::cout <<  std::endl;
//    }
//
//    // uint8_t *p = (uint8_t *)cmd.get_motor_send_data();
//    // for(int i =0; i<17; i++)
//    // printf("0X%02X ", *p++);
////     usleep(200);
//
////  }
//
//}

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
//      cmd.W     =atof(argv[1]);
    cmd.W     =50;
    cmd.T     = 0.0;
    serial.sendRecv(&cmd,&data);

    cmd.id    = 1;
    cmd.mode  = 1;
    cmd.K_P   = 0.0;
    cmd.K_W   = 0.0;
    cmd.Pos   = 0.0;
//      cmd.W     =atof(argv[1]);
    cmd.W     =0.0;
    cmd.T     = 0.0;
    serial.sendRecv(&cmd,&data);
    cout << cmd.W << endl;

    return 0;
}