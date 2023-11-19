import pyvisa
import time
import subprocess


rm = pyvisa.ResourceManager()
print(rm.list_resources())
siglent = rm.open_resource('USB0::62700::4609::SDM35HBX7R0574::0::INSTR')
print(siglent.query('*IDN?'))

output = subprocess.run(["../build/motorctrl", "25"], capture_output=True, text=True)
print(output.stdout)
print(siglent.query('MEAS:VOLT:DC?'))
print(siglent.query('MEAS:VOLT:DC?'))

output = subprocess.run(["../build/motorctrl", "45"], capture_output=True, text=True)
print(output.stdout)
print(siglent.query('MEAS:VOLT:DC?'))
print(siglent.query('MEAS:VOLT:DC?'))

output = subprocess.run(["../build/motorctrl", "25"], capture_output=True, text=True)
print(output.stdout)
print(siglent.query('MEAS:VOLT:DC?'))
print(siglent.query('MEAS:VOLT:DC?'))

output = subprocess.run(["../build/stop"], capture_output=True, text=True)
print(output.stdout)

siglent.close()