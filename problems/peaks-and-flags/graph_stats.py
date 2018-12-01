import csv
import matplotlib.pyplot as plt
import numpy as np

kInputFileName = 'time_stats.txt'

csv_file = open(kInputFileName, 'rt')
csv_reader = csv.reader(csv_file, delimiter=':')
sizes = []
runtimes = []
for row in csv_reader:
  if (len(row) == 2):
    size, runtime = row
    sizes.append(int(size))
    runtimes.append(float(runtime))
  
fig, ax = plt.subplots()
ax.plot(sizes, runtimes)
plt.savefig('runtime_data_plot.png')
plt.show()
