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
motor0 = defaultdict(lambda: {
    'id': 0,
    'K_P': 0.0,
    'K_W': 0.0,
    'Pos': 0.0,
    'W': 0.0 * GEAR_RATIO,
    'T': 0.0,
})

# motor1: testing motor, torque mode
motor1 = defaultdict(lambda: {
    'id': 1,
    'K_P': 0.0,
    'K_W': 0.0,
    'Pos': 0.0,
    'W': 0.0 * GEAR_RATIO,
    'T': 0.0,
})

MIN_TORQUE = 0.5
MAX_TORQUE = 3
TORQUE_STEP = 0.05
MIN_SPEED = 2 * GEAR_RATIO
MAX_SPEED = 10 * GEAR_RATIO
SPEED_STEP = 0.5 * GEAR_RATIO


def stop_motor():
    output = subprocess.run(["../build/stop"], capture_output=True, text=True)
    print(output.stdout)


def motor_test_runner(minTorque: float = MIN_TORQUE, maxTorque: float = MAX_TORQUE, torqueStep: float = TORQUE_STEP, \
                      minSpeed: float = MIN_SPEED, maxSpeed: float = MAX_SPEED, speedStep: float = SPEED_STEP, \
                      runtime: int = 3):
    # Path: unitree/python_control/control.py
    import pyvisa
    import time
    import subprocess

    rm = pyvisa.ResourceManager()
    # print(rm.list_resources())
    result = pd.DataFrame(columns=['input_speed', 'input_torque', 'voltage', 'output_speed', 'output_torque', 'temp'])
    pattern = r"motor\.Temp: (\d+) ℃\nmotor\.W: ([\d.]+) rad/s\nmotor\.T: ([\d.]+) N\.m"

    for speed in np.arange(minSpeed, maxSpeed, speedStep):
        motor0['W'] = speed

        # subprocess.run(["../build/motorctrl",
        #                 str(motor0['id']),
        #                 str(motor0['K_P']),
        #                 str(motor0['K_W']),
        #                 str(motor0['Pos']),
        #                 str(motor0['W']),
        #                 str(motor0['T']), ], capture_output=False)

        for torque in np.arange(minTorque, maxTorque, torqueStep):
            print(f"speed: {speed}, torque: {torque}")

            motor1['T'] = torque
            for _ in range(runtime):

                time.sleep(.5)

        print('Writting file to csv...')
        result.to_csv('../data/go1.csv')




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
