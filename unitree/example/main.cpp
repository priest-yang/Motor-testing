#include "serialPort/SerialPort.h"
#include <unistd.h>
#include "preprogrammed.h"



int main(int argc, char** argv) {
//argv 1= id, argv 2 = K_P, argv3 = k_w argv 4 = pos, argv 5 = w, argv 6= T
  SerialPort  serial("/dev/ttyUSB0");
  MotorCmd    cmd;
  MotorData   data;
double pos = 0;
int flag = 0;
//  while(true) {
    cmd.motorType = MotorType::GO_M8010_6;
//    cmd.id    = 0;
//    cmd.mode  = 1;
//    cmd.K_P   = 0.0;
//    cmd.K_W   = 0.05;
//    cmd.Pos   = 0.0;
//    cmd.W     = 6.28*6.33;
//    cmd.T     = 0.0;

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
      cmd.id    = atoi(argv[1]);
      cmd.mode  = 1;
      cmd.K_P   = atof(argv[2]);
      cmd.K_W   = atof(argv[3]);
      cmd.Pos   = atof(argv[4]);
//      cmd.W     =atof(argv[1]);
    cmd.W     =atof(argv[5]);
      cmd.T     = atof(argv[6]);

      int use_PID = atoi(argv[7]);
      if(use_PID == 1){
          //use PID to control
          bool is_done = PID_control(cmd, data, serial);
//          if(is_done){
//              std::cout << "is done\n";
//          }
      } else{
          serial.sendRecv(&cmd,&data);
      }

//torque mode
//      cmd.id    = 1;
//      cmd.mode  = 1;
//      cmd.K_P   = 0.0;
//      cmd.K_W   = 0.0;
//      cmd.Pos   = 0.0;
//      cmd.W     = 0.0;
//      cmd.T     = 0.0;
      usleep(300000);
      serial.sendRecv(&cmd,&data);


//      cmd.id    = 0;
//      cmd.mode  = 1;
//      cmd.K_P   = 0.0;
//      cmd.K_W   = 0.09;
//      cmd.Pos   = 0.0;
//      cmd.W     = 12;
//      cmd.T     = 0.02;
//      serial.sendRecv(&cmd,&data);

      while(data.correct == true)
      {
//          std::cout <<  std::endl;
//          std::cout <<  "motor.Pos: "    << data.Pos    << " rad" << std::endl;
          std::cout <<  "motor.Temp: "   << data.Temp   << " ℃"  << std::endl;
          std::cout <<  "motor.W: "      << data.W      << " rad/s"<<std::endl;
          std::cout <<  "motor.T: "      << data.T      << " N.m" << std::endl;


//          std::cout <<  "motor.MError: " << data.MError <<  std::endl;
//          std::cout <<  std::endl;
      }
//      usleep(3000000);
    return 0;
  }

//}
