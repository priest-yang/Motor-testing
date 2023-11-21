import pyvisa
import time
import subprocess


output = subprocess.run(["../build/PID_helper", "25"], capture_output=True, text=True)

double_output = float(output)

