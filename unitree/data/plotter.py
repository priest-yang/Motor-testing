import csv
import matplotlib.pyplot as plt
import numpy as np


def read_csv(file_path):
    with open(file_path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        headers = next(reader)
        data = {header: [] for header in headers}

        for row in reader:
            for i, value in enumerate(row):
                data[headers[i]].append(float(value.strip()))

    return data

    # File path to your CSV file


file_path = 'go1_with_all.csv'  # Replace 'your_file.csv' with the actual file path

# Read data from CSV
data = read_csv(file_path)

# Extracting relevant columns
torque_cmd = data['input_torque']
voltage = np.asarray(data['voltage'])
torque_measured = -voltage * 1000 * 5.0122

# Plotting the scatter plot
plt.scatter(torque_cmd, torque_measured, marker='o')
plt.title('Scatter Plot: Input Torque vs. Voltage')
plt.xlabel('Torque Command [Nm]')
plt.ylabel('Torque Sensor [Nm]')
plt.grid(True)
plt.show()