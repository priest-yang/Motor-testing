#include "serialPort/SerialPort.h"
#include <unistd.h>

/*Global variable*/
double K_I = 0.0
double K_D = 0.0


bool PID_control(MotorCmd cmd, MotorData data){
    // cmd: command to be sent to the motor
    // data: data received from the motor
    // return: true if the motor has reached the target speed, false otherwise

    serial.sendRecv(&cmd,&data);
    // usleep(50000);
    if (cmd.W == 0){
        // tested motor, directly return True
        return true;
    }

    if ((data.W - cmd.W) / cmd.W > 0.05 && data.W - cmd.W > 1) {
        // PID controller
        int iter = 0

        double error_accum = 0
        double error = 0

        for (int intr; iter < 50; iter++){
            serial.sendRecv(&cmd,&data);
            usleep(50000);
            // if received motor's data is broken, try 3 times
            if (data.correct == false){
                int temp = 0;
                while (data.correct == false and temp < 3){
                    usleep(50000);
                    serial.sendRecv(&cmd,&data);
                    if (data.correct == true){
                        break;
                    }
                    temp += 1;
                }
                return false;
            }

            if (std::abs((data.W - cmd.W) / cmd.W) <= 0.05 || std::abs(data.W - cmd.W) < 1){
                return true;
            }

            error = cmd.W - data.W;
            error_accum += error;

            Tor_fb =  K_W * error + K_I * error_accum;
            Tor_ff = 0; // not implented yet
            cmd.T = Tor_fb + Tor_ff;
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
    cmd.id    = atoi(argv[1]);
    cmd.mode  = 1;
    cmd.K_P   = atof(argv[2]);
    cmd.K_W   = atof(argv[3]);
    cmd.Pos   = atof(argv[4]);
    cmd.W     = atof(argv[5]);
    cmd.T     = atof(argv[6]);

    
    // wait motor to reach the target speed
    usleep(50000);
    control_flag = PID_control(&cmd, &data);
    if (control_flag != true){
        std::cout << "Motor has not reached the target speed" << std::endl;
    }

    serial.sendRecv(&cmd,&data);

    if(data.correct == true)
    {
        std::cout <<  "motor.Temp: "   << data.Temp   << " ℃"  << std::endl;
        std::cout <<  "motor.W: "      << data.W      << " rad/s"<<std::endl;
        std::cout <<  "motor.T: "      << data.T      << " N.m" << std::endl;
    }

    return 0;
}