import serial
import struct
import time
import pandas as pd
# Configure the serial connection
ser = serial.Serial(
    port='/dev/ttyACM0',  # Replace with your serial port if need be
    baudrate=115200,
    timeout=1
)
speed_list = []
vint_list = []
current_output_list = []
torque_list = []
current_measured_list = []
command_torque_list = []
data_all = {'speed': speed_list, 'v_int': vint_list, 'current_output': current_output_list, 'torque': torque_list,
        'current_measured': current_measured_list, 'command_torque': command_torque_list}
# Wait for the incoming data
while True:
    # Read 10 bytes from the UART
    data = ser.read(16)
    # Make sure we have 10 bytes
    if len(data) == 16:
        # Unpack the data
        # '<' means little-endian, 'f' means float, 'h' means short (int16_t)
        speed, v_int, torque_value, current_value, command_torque, cur_measured = struct.unpack('<fhhhfh', data)
        print(f'Speed: {speed}, v_int: {v_int}, torque_value: {torque_value}, current_value: {current_value}, command_torque: {command_torque}, cur_measured: {cur_measured}')
        speed, v_int, torque_value, current_value, command_torque, cur_measured = \
            int(speed), int(v_int), int(torque_value), int(current_value), int(command_torque), int(cur_measured)
        speed_list.append(speed)
        vint_list.append(v_int)
        current_output_list.append(current_value)
        torque_list.append(torque_value)
        current_measured_list.append(cur_measured)
        command_torque_list.append(command_torque)
    else:
        print(f'Incomplete data received: {data}')
    if len(speed_list) > 100:
        data_all['speed'].extend(speed_list)
        data_all['v_int'].extend(vint_list)
        data_all['current_output'].extend(current_output_list)
        data_all['torque'].extend(torque_list)
        data_all['current_measured'].extend(current_measured_list)
        data_all['command_torque'].extend(command_torque_list)
        speed_list, vint_list, current_output_list, torque_list, current_measured_list, command_torque_list = [], [], [], [], [], []
        df = pd.DataFrame(data_all)
        df.to_csv('data.csv')
        print('Writing to CSV...')

