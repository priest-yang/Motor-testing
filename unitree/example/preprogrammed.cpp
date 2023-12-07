//
// Created by xuzhekai on 18/11/23.
//

#include "preprogrammed.h"

bool PID_control(MotorCmd& cmd, MotorData& data, SerialPort& serial_port){
    // cmd: command to be sent to the motor
    // data: data received from the motor
    // return: true if the motor has reached the target speed, false otherwise

    serial_port.sendRecv(&cmd,&data);
    usleep(5000);
    if (cmd.W == 0){
        // tested motor, directly return True
        return true;
    }

    if (std::abs((data.W - cmd.W) / cmd.W) > 0.01 && std::abs(data.W - cmd.W) > 0.1) {
        // PID controller

        double error_accum = 0;
        double error = 0;

        for (int iter = 0; iter < 50; iter++){
            serial_port.sendRecv(&cmd,&data);
            usleep(50000);
            // if received motor's data is broken, try 3 times
            if (!data.correct){
                int temp = 0;
                while ((!data.correct) && temp < 3){
                    usleep(50000);
                    serial_port.sendRecv(&cmd,&data);
                    if (data.correct){
                        break;
                    }
                    temp += 1;
                }
                return false;
            }

            if (std::abs((data.W - cmd.W) / cmd.W) <= 0.01 || std::abs(data.W - cmd.W) < 0.1){
                return true;
            }

            error = cmd.W - data.W;
//            std::cout <<error_accum << std::endl;
            error_accum += error;

            double Tor_fb =  K_D * error + K_I * error_accum;

            cmd.T = Tor_fb + Tor_ff;
        }

        // PID controller failed
        return false;

    }else{
        return true;
    }
}
