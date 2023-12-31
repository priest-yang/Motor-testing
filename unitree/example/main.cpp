#include "serialPort/SerialPort.h"
#include <unistd.h>
#include "preprogrammed.h"



int main(int argc, char** argv) {
//argv 1= id, argv 2 = K_P, argv3 = k_w argv 4 = pos, argv 5 = w, argv 6= T
  SerialPort  serial("/dev/ttyUSB0");
//  SerialPort  serial2("/dev/ttyUSB1");
  MotorCmd    cmd;
  MotorData   data;

    cmd.motorType = MotorType::GO_M8010_6;

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

//    cmd.id    = 0;
//    cmd.mode  = 1;
//    cmd.K_P   = 0;
//    cmd.K_W   = 0;
//    cmd.Pos   = 0;
//    cmd.W     =;
//    cmd.T     = ;

//    int use_PID = 0;
      if(use_PID == 1){
          //use PID to control
              PID_impl(cmd,data,serial);
      } else{
              serial.sendRecv(&cmd,&data);
      }

      usleep(3000);
      serial.sendRecv(&cmd,&data);


//      cmd.id    = 0;
//      cmd.mode  = 1;
//      cmd.K_P   = 0.0;
//      cmd.K_W   = 0.09;
//      cmd.Pos   = 0.0;
//      cmd.W     = 12;
//      cmd.T     = 0.02;
//      serial.sendRecv(&cmd,&data);

//      while(data.correct == true)
//      {
//          std::cout <<  std::endl;
//          std::cout <<  "motor.Pos: "    << data.Pos    << " rad" << std::endl;
          std::cout <<  "motor.Temp: "   << data.Temp   << " ℃"  << std::endl;
          std::cout <<  "motor.W: "      << data.W      << " rad/s"<<std::endl;
          std::cout <<  "motor.T: "      << data.T      << " N.m" << std::endl;


//          std::cout <<  "motor.MError: " << data.MError <<  std::endl;
//          std::cout <<  std::endl;
//      }
//      usleep(3000000);
    return 0;
  }

//}
