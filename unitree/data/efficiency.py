import csv
import numpy as np
import matplotlib.pyplot as plt


# Function to read CSV file and extract data
def read_csv(file_path):
    with open(file_path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        headers = next(reader)
        data = {header: [] for header in headers}

        for row in reader:
            for i, value in enumerate(row):
                data[headers[i]].append(float(value.strip()))

    return data


# File paths to your CSV files
dc_file_path = 'sweep1_DC.csv'  # Replace 'sweep1_DC.csv' with the actual file path
ac_file_path = 'sweep1_AC.csv'  # Replace 'sweep1_AC.csv' with the actual file path

# Read data from DC file
dc_data = read_csv(dc_file_path)

# Extracting relevant columns from DC file
dc_speed = dc_data['output_speed']
dc_voltage = dc_data['voltage']

# Calculate torque
torque = [abs(volt) * 1000 * 5.0122 for volt in dc_voltage]

# Apply abs() element-wise to dc_speed
abs_dc_speed = [abs(speed) for speed in dc_speed]

# Calculate output power
output_power = [speed * t for speed, t in zip(dc_speed, torque)]

# Read data from AC file
ac_data = read_csv(ac_file_path)

# Extracting relevant columns from AC file
ac_voltage = ac_data['voltage']

# Calculate input power
input_power = [24 * (v / 0.05) for v in ac_voltage]

# Calculate efficiency
efficiency = [op / ip if ip != 0 else 0 for op, ip in zip(output_power, input_power)]

# Reshape data for heatmap
print(len(abs_dc_speed))
heatmap_data = np.array(efficiency).reshape(len(abs_dc_speed), -1)

# Plotting the heatmap
plt.imshow(heatmap_data, cmap='viridis', origin='lower', aspect='auto',
           extent=(min(abs_dc_speed), max(abs_dc_speed), min(torque), max(torque)))
plt.colorbar(label='Efficiency')
plt.title('Efficiency Heatmap')
plt.xlabel('Absolute Output Speed')
plt.ylabel('Torque')
plt.grid(True)
plt.show()
