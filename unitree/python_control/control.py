import pyvisa
import time
import subprocess
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
import re

GEAR_RATIO = 6.33

# motor0: driving motor, speed mode
motor0 = {
    'id': 0,
    'K_P': 0.0,
    'K_W': 0.1,
    'Pos': 0.0,
    'W': 0.0 * GEAR_RATIO,
    'T': 0.0,
}

# motor1: testing motor, torque mode
motor1 = {
    'id': 1,
    'K_P': 0.0,
    'K_W': 0.0,
    'Pos': 0.0,
    'W': 0.0 * GEAR_RATIO,
    'T': 0.0,
}

MIN_TORQUE = 0.5
MAX_TORQUE = 1.5
TORQUE_STEP = 0.05
MIN_SPEED = 2 * GEAR_RATIO
MAX_SPEED = 10 * GEAR_RATIO
SPEED_STEP = 0.5 * GEAR_RATIO


def stop_motor():
    # output = subprocess.run(["../build/stop"], capture_output=True, text=True)
    # print(output.stdout)
    print("do nothing")


def motor_test_runner(minTorque: float = MIN_TORQUE, maxTorque: float = MAX_TORQUE, torqueStep: float = TORQUE_STEP, \
                      minSpeed: float = MIN_SPEED, maxSpeed: float = MAX_SPEED, speedStep: float = SPEED_STEP, \
                      runtime: int = 3):
    # Path: unitree/python_control/control.py
    import pyvisa
    import time
    import subprocess

    rm = pyvisa.ResourceManager()
    # print()rm.list_resources())
    siglent = rm.open_resource(rm.list_resources()[0])
    result = pd.DataFrame(columns=['input_speed', 'input_torque', 'voltage', 'output_speed', 'output_torque', 'temp'])
    pattern = r"[\s\S]+ ([-|\d]+)[\s\S]+ ([-|\d.]+)[\s\S]+ ([-|\d.]+)"

    for speed in np.arange(minSpeed, maxSpeed, speedStep):
        cur_speed = speed
        motor0['W'] = cur_speed
        _ = subprocess.run(["../build/motorctrl",
                            str(motor0['id']),
                            str(motor0['K_P']),
                            str(motor0['K_W']),
                            str(motor0['Pos']),
                            str(motor0['W']),
                            str(motor0['T']), ], capture_output=True, text=True)

        for torque in np.arange(minTorque, maxTorque, torqueStep):
            print(f"speed: {cur_speed}, torque: {torque}")

            motor1['T'] = torque

            for _ in range(runtime):

                output = subprocess.run(["../build/motorctrl",
                                         str(motor1['id']),
                                         str(motor1['K_P']),
                                         str(motor1['K_W']),
                                         str(motor1['Pos']),
                                         str(motor1['W']),
                                         str(motor1['T']), ], capture_output=True, text=True)

                match = re.search(pattern, output.stdout)

                if match:
                    temp = int(match.group(1))
                    speed = float(match.group(2))
                    torque = float(match.group(3))

                    result_dict = {'temp': temp, 'output_speed': speed, 'output_torque': torque}
                    result_dict.update({'input_speed': motor0['W'], 'input_torque': motor1['T']})
                    cur_df = pd.Series(data=result_dict).to_frame().T

                    if temp > 45:
                        print(f"Overheat!!, temp: {temp}")
                        stop_motor()
                        break
                else:
                    cur_df = pd.DataFrame()
                    print("No match!!")
                    print(output.stdout)
                    stop_motor()

                cur_df['voltage'] = siglent.query('MEAS:VOLT:DC?')
                result = pd.concat([result, cur_df], ignore_index=True)

                time.sleep(.5)
        print('Writting file to csv...')
        result.to_csv('../data/go1.csv')

    siglent.close()


if __name__ == '__main__':
    # stop_motor()
    motor_test_runner()

# siglent = rm.open_resource('USB0::62700::4609::SDM35HBX7R0574::0::INSTR')
# print(siglent.query('*IDN?'))

# output = subprocess.run(["../build/motorctrl", "25"], capture_output=True, text=True)
# print(output.stdout)
# print(siglent.query('MEAS:VOLT:DC?'))
# print(siglent.query('MEAS:VOLT:DC?'))

# output = subprocess.run(["../build/motorctrl", "45"], capture_output=True, text=True)
# print(output.stdout)
# print(siglent.query('MEAS:VOLT:DC?'))
# print(siglent.query('MEAS:VOLT:DC?'))

# output = subprocess.run(["../build/motorctrl", "25"], capture_output=True, text=True)
# print(output.stdout)
# print(siglent.query('MEAS:VOLT:DC?'))
# print(siglent.query('MEAS:VOLT:DC?'))

# output = subprocess.run(["../build/stop"], capture_output=True, text=True)
# print(output.stdout)

# siglent.close()
