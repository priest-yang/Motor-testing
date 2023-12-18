//
// Created by xuzhekai on 18/11/23.
//

#include "preprogrammed.h"


bool PID_control(MotorCmd& cmd, MotorData& data, SerialPort& serial_port){
    // cmd: command to be sent to the motor
    // data: data received from the motor
    // return: true if the motor has reached the target speed, false otherwise
    std::string path_to_logging= "../data/driving_motor/logging.csv";
    // open the logging file
    std::ofstream csvFile(path_to_logging, std::ios::app);
    if (!csvFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
    }

    serial_port.sendRecv(&cmd,&data);
    usleep(2000);

    if (cmd.W == 0){
        // tested motor, directly return True
        return true;
    }

    if (std::abs((data.W - cmd.W) / cmd.W) > 0.01 && std::abs(data.W - cmd.W) > 0.1) {

        // PID controller
        double error_accum = 0;
        double error = 0;

        for (int iter = 0; iter < 8000000; iter++){
            auto start_time = std::chrono::high_resolution_clock::now();

            serial_port.sendRecv(&cmd,&data);
            usleep(2000);
            // if received motor's data is broken, try 3 times
            if (!data.correct){
                int temp = 0;
                while ((!data.correct) && temp < 3){
                    usleep(1000);
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

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

            error = cmd.W - data.W;
            error_accum += error * double(duration.count()) / 1000;
            if (error_accum > max_I){
                error_accum = max_I;
            } else if (-error_accum > max_I){
                error_accum = -max_I;
            }

            double Tor_fb =  K_P * error + K_I * error_accum;

            cmd.T = float(Tor_fb + Tor_ff);
            serial_port.sendRecv(&cmd,&data);
            usleep(2000);
            // std::cout << cmd.T << std::endl;
            csvFile << cmd.W << " , " << data.W << " , " << error_accum << " , " << error << std::endl;

        }
        // PID controller failed
        csvFile.close();
        return true;
    }else{
        csvFile.close();
        return true;
    }

}
