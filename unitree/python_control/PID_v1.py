import pyvisa
import time
import subprocess
#
#
# output = subprocess.run(["../build/PID_helper", "25"], capture_output=True, text=True)
#
# double_output = float(output)
# #
#
# rm = pyvisa.ResourceManager()
# print(rm.list_resources())

import pandas as pd
# print(pd.__version__)
dic = {'temp': 30, 'output_speed': 9.52297, 'output_torque': 0.492188, 'input_speed': 12.66, 'input_torque': 0.5}
df = pd.DataFrame(data=dic, index=None)
print(df)
