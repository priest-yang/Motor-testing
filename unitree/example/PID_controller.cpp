#include "serialPort/SerialPort.h"
#include <unistd.h>
#include <chrono>

/*Global variable*/
double K_I = 0.0011; // 0.01 / 1000;
double max_I = 1;
double K_P = 0.015; //0.01;
double Tor_ff = 0.092;


bool PID_control(MotorCmd& cmd, MotorData& data, SerialPort& serial_port){
    // cmd: command to be sent to the motor
    // data: data received from the motor
    // return: true if the motor has reached the target speed, false otherwise

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

        for (int iter = 0; iter < 5000000; iter++){
            auto start_time = std::chrono::high_resolution_clock::now();

            serial_port.sendRecv(&cmd,&data);
            usleep(2000);
            // if received motor's data is broken, try 3 times
            if (!data.correct){
                int temp = 0;
                while ((!data.correct) && temp < 3){
                    usleep(2000);
                    serial_port.sendRecv(&cmd,&data);
                    if (data.correct){
                        break;
                    }
                    temp += 1;
                }
                return false;
            }

//            if (std::abs((data.W - cmd.W) / cmd.W) <= 0.01 || std::abs(data.W - cmd.W) < 0.1){
//                return true;
//            }

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

            error = cmd.W - data.W;
            error_accum += error * double(duration.count()) / 1000;
            if (error_accum > max_I){
                error_accum = max_I;
            }

            double Tor_fb =  K_P * error + K_I * error_accum;

            cmd.T = float(Tor_fb + Tor_ff);
            serial_port.sendRecv(&cmd,&data);
            usleep(2000);
            // std::cout << cmd.T << std::endl;
        }
        // PID controller failed
        return false;

    }else{
        return true;
    }
}

int main(int argc, char** argv) {
//argv 1= id, argv 2 = K_P, argv3 = k_w argv 4 = pos, argv 5 = w, argv 6= T

    SerialPort  serial("/dev/ttyUSB0");
    MotorCmd    cmd;
    MotorData   data;

    double pos = 0;
    int flag = 0;

    cmd.motorType = MotorType::GO_M8010_6;
    cmd.id    = 1;
    cmd.mode  = 1;
    cmd.K_P   = 0.0;
    cmd.K_W   = 0.0;
    cmd.Pos   = 0.0;
    cmd.W     = 0.0;
    cmd.T     = 0;
    serial.sendRecv(&cmd,&data);


    cmd.id    = atoi(argv[1]);
    cmd.mode  = 1;
    cmd.K_P   = atof(argv[2]);
    cmd.K_W   = atof(argv[3]);
    cmd.Pos   = atof(argv[4]);
    cmd.W     = atof(argv[5]);
    cmd.T     = atof(argv[6]);

    
    // wait motor to reach the target speed
    usleep(50000);
//    bool control_flag = true;
    bool control_flag = PID_control(cmd, data, serial);
    if (!control_flag){
        std::cout << "Motor has not reached the target speed" << std::endl;
    }
    usleep(500000);

    while(true){
        serial.sendRecv(&cmd,&data);

        if(data.correct)
        {
            std::cout <<  "motor.Temp: "   << data.Temp   << " ℃"  << std::endl;
            std::cout <<  "motor.W: "      << data.W      << " rad/s"<<std::endl;
            std::cout <<  "motor.T: "      << data.T      << " N.m" << std::endl;
        }
        usleep(1000000);

    }


    return 0;
}