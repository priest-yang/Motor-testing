import pyvisa
import time
import subprocess
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
import re

GEAR_RATIO = 6.33

MIN_TORQUE = 1
MAX_TORQUE = 2
TORQUE_STEP = 0.05
MIN_SPEED = - 1 * GEAR_RATIO
MAX_SPEED = - 39 * GEAR_RATIO
SPEED_STEP = - 3 * GEAR_RATIO

# motor0: driving motor, speed mode
motor0 = {
    'id': 0,
    'K_P': 0.0,
    'K_W': 0.1,
    'Pos': 0.0,
    'W': 0.0 * GEAR_RATIO,
    'T': 0.0,
    'PID': 1,
}

# motor1: testing motor, torque mode
motor1 = {
    'id': 1,
    'K_P': 0.0,
    'K_W': 0.0,
    'Pos': 0.0,
    'W': 0.0 * GEAR_RATIO,
    'T': 0.0,
    'PID': 0,
}

def stop_motor():
    # output = subprocess.run(["../build/stop"], capture_output=True, text=True)
    # print(output.stdout)
    print("stop motor (not implemented)")


def adjust_PD(current_speed):
    '''
    Adjust K_P and K_W according to current speed
    Input: current motor speed
    Output: True if K_P and K_W are adjusted, False otherwise
    '''
    global motor0
    if abs((abs(current_speed) - abs(motor0['W'])) / abs(motor0['W'])) > 0.2 and abs(current_speed) - abs(motor0['W']) > 3:
        cur_kw = motor0['K_W']
        motor0['K_W'] = motor0['K_W'] + 0.01
        print(f"adjust the K_W from {cur_kw} to {motor0['K_W']}")

        _ = subprocess.run(["../build/motorctrl",
                            str(motor0['id']),
                            str(motor0['K_P']),
                            str(motor0['K_W']),
                            str(motor0['Pos']),
                            str(motor0['W']),
                            str(motor0['T']),
                            str(motor0['PID'])], capture_output=True, text=True)
        return True
    else:
        return False


def motor_test_runner(minTorque: float = MIN_TORQUE, maxTorque: float = MAX_TORQUE, torqueStep: float = TORQUE_STEP,
                      minSpeed: float = MIN_SPEED, maxSpeed: float = MAX_SPEED, speedStep: float = SPEED_STEP,
                      runtime: int = 3):
    # Path: unitree/python_control/control.py
    import pyvisa
    import time
    import subprocess

    rm = pyvisa.ResourceManager()
    print(rm.list_resources())
    siglent = rm.open_resource(rm.list_resources()[0])
    # _=siglent.query('CONF:VOLT:DC')
    # _=siglent.query('VOLT:DC:NPLC 1')
    # _ = siglent.query('CONF:VOLT:DC')
    # print("configure complete")
    # siglent.query('MEAS:VOLT:DC?')

    result = pd.DataFrame(columns=['input_speed', 'input_torque', 'voltage', 'output_speed', 'output_torque', 'temp'])
    pattern = r"[\s\S]+ ([-|\d]+)[\s\S]+ ([-|\d.]+)[\s\S]+ ([-|\d.]+)"
    for torque in np.arange(minTorque, maxTorque, torqueStep):
        motor1['T'] = torque
        _ = subprocess.run(["../build/motorctrl",
                                         str(motor1['id']),
                                         str(motor1['K_P']),
                                         str(motor1['K_W']),
                                         str(motor1['Pos']),
                                         str(motor1['W']),
                                         str(motor1['T']),
                                         str(motor1['PID'])], capture_output=True, text=True)
        _ = subprocess.run(["../build/motorctrl",
                            str(motor0['id']),
                            str(motor0['K_P']),
                            str(motor0['K_W']),
                            str(motor0['Pos']),
                            str(minSpeed),
                            str(motor0['T']),
                            str(0)], capture_output=True, text=True)

        time.sleep(0.3)

        for speed in np.arange(minSpeed, maxSpeed, speedStep):

            cur_speed = speed
            motor0['W'] = cur_speed
            print(f"speed: {cur_speed}, torque: {torque}")

            for _ in range(runtime):
                output = subprocess.run(["../build/motorctrl",
                                         str(motor0['id']),
                                         str(motor0['K_P']),
                                         str(motor0['K_W']),
                                         str(motor0['Pos']),
                                         str(motor0['W']),
                                         str(motor0['T']),
                                         str(motor0['PID'])], capture_output=True, text=True)

                time.sleep(0.3)


                driving_output = subprocess.run(["../build/motorctrl",
                            str(motor0['id']),
                            str(motor0['K_P']),
                            str(motor0['K_W']),
                            str(motor0['Pos']),
                            str(motor0['W']),
                            str(motor0['T']),
                            str(motor0['PID'])], capture_output=True, text=True)

                output = subprocess.run(["../build/motorctrl",
                                         str(motor1['id']),
                                         str(motor1['K_P']),
                                         str(motor1['K_W']),
                                         str(motor1['Pos']),
                                         str(motor1['W']),
                                         str(motor1['T']),
                                         str(motor1['PID'])], capture_output=True, text=True)

                match = re.search(pattern, output.stdout)
                match_driving_output = re.search(pattern, driving_output.stdout)

                if match and match_driving_output:
                    # print("getting a match!")
                    temp = int(match.group(1))
                    # speed = float(match.group(2))
                    speed = float(match.group(2))
                    torque = float(match.group(3))
                    print(temp)
                    print(speed)
                    print(torque)
                    result_dict = {'temp': temp, 'output_speed': speed, 'output_torque': torque}
                    result_dict.update({'input_speed': motor0['W'], 'input_torque': motor1['T']})
                    cur_df = pd.Series(data=result_dict).to_frame().T

                    if temp > 80:
                        print(f"Overheat!!, temp: {temp}")
                        stop_motor()
                        break
                else:
                    cur_df = pd.DataFrame()
                    print("No match!!")
                    print(output.stdout)
                    stop_motor()

                adjust_flag = adjust_PD(speed)

                if not adjust_flag:  # if K_P and K_W are not adjusted, then read voltage and record data
                    cur_df['voltage'] = siglent.query('MEAS:VOLT:DC?')
                    result = pd.concat([result, cur_df], ignore_index=True)
                else:
                    time.sleep(3)

        print('Writing file to csv...')
        result.to_csv('../data/sweep3_DC.csv')

    siglent.close()


if __name__ == '__main__':
    # stop_motor()
    motor_test_runner()

