#include "serialPort/SerialPort.h"
#include <unistd.h>
#include "preprogrammed.h"



int main() {

  SerialPort  serial("/dev/ttyUSB0");
  MotorCmd    cmd;
  MotorData   data;
double pos = 0;
int flag = 0;
  while(true) {
    cmd.motorType = MotorType::GO_M8010_6;
//    cmd.id    = 0;
//    cmd.mode  = 1;
//    cmd.K_P   = 0.0;
//    cmd.K_W   = 0.05;
//    cmd.Pos   = 0.0;
//    cmd.W     = 6.28*6.33;
//    cmd.T     = 0.0;
//if(pos < 3.14){
//    pos += 0.01;
//}else if(pos > 0){
//    pos -= 0.05;
//}
if (pos >3.14){
    flag = 1;
}
if (pos < 0){
    flag = 0;
}
if(flag == 0){
    pos+=0.01;
}else{
    pos-=0.01;
}
      std::cout << pos << std::endl;
////position mode
//      cmd.id    = 0;
//      cmd.mode  = 1;
//      cmd.K_P   = 0.01;
//      cmd.K_W   = 0.02;
//      cmd.Pos   = 3.14*6.33;
//      cmd.W     = 0.0;
//      cmd.T     = 0.0;

//damping mode
//      cmd.id    = 0;
//      cmd.mode  = 1;
//      cmd.K_P   = 0.0;
//      cmd.K_W   = 0.0;
//      cmd.Pos   = 0.0;
//      cmd.W     = 0.0;
////      cmd.T     = -0.035;
//      if(data.W >0){
//          cmd.T  = 0.035;
//      }else{
//          cmd.T = -0.035;
//      }
//speed mode
      cmd.id    = 0;
      cmd.mode  = 1;
      cmd.K_P   = 0.0;
      cmd.K_W   = 0.15;
      cmd.Pos   = 0.0;
      cmd.W     =25;
      cmd.T     = 0.02;
    serial.sendRecv(&cmd,&data);
//torque mode
      cmd.id    = 1;
      cmd.mode  = 1;
      cmd.K_P   = 0.0;
      cmd.K_W   = 0.0;
      cmd.Pos   = 0.0;
      cmd.W     = 0.0;
      cmd.T     = 0.5;

      serial.sendRecv(&cmd,&data);
//      usleep(2000000);

//      cmd.id    = 0;
//      cmd.mode  = 1;
//      cmd.K_P   = 0.0;
//      cmd.K_W   = 0.09;
//      cmd.Pos   = 0.0;
//      cmd.W     = 12;
//      cmd.T     = 0.02;
      serial.sendRecv(&cmd,&data);

      if(data.correct == true)
      {
          std::cout <<  std::endl;
          std::cout <<  "motor.Pos: "    << data.Pos    << " rad" << std::endl;
          std::cout <<  "motor.Temp: "   << data.Temp   << " ℃"  << std::endl;
          std::cout <<  "motor.W: "      << data.W      << " rad/s"<<std::endl;
          std::cout <<  "motor.T: "      << data.T      << " N.m" << std::endl;
          std::cout <<  "motor.MError: " << data.MError <<  std::endl;
          std::cout <<  std::endl;
      }
      usleep(3000000);

//      cmd.motorType = MotorType::GO_M8010_6;
//      cmd.id    = 0;
//      cmd.mode  = 0;
//      cmd.K_P   = 0.0;
//      cmd.K_W   = 0.00;
//      cmd.Pos   = 0.0;
//      cmd.W     = 0;
//      cmd.T     = 0.0;
//      serial.sendRecv(&cmd,&data);

//      cmd.motorType = MotorType::GO_M8010_6;
//      cmd.id    = 1;
//      cmd.mode  = 0;
//      cmd.K_P   = 0.0;
//      cmd.K_W   = 0.00;
//      cmd.Pos   = 0.0;
//      cmd.W     = 0;
//      cmd.T     = 0.0;
//      serial.sendRecv(&cmd,&data);

//      usleep(5000000);

  }

}
