import csv
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
dc_file_path = 'sweep1_DC.csv'
ac_file_path = 'sweep1_AC.csv'

# Read data from DC file
dc_data = read_csv(dc_file_path)

# Extracting relevant columns from DC file
dc_speed = dc_data['output_speed']
dc_voltage = dc_data['voltage']

# Calculate torque
Torque = [abs(volt) * 1000 * 5.0122 for volt in dc_voltage]
abs_dc_speed = [abs(speed) for speed in dc_speed]

# Plotting the efficiency
plt.plot(abs_dc_speed, Torque, marker='o')
plt.title('Plot')
plt.xlabel('Output Speed')
plt.ylabel('Torque')
plt.grid(True)
plt.show()
