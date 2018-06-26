import os
import sys

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.collections import PolyCollection
from matplotlib.collections import LineCollection
from matplotlib.colors import colorConverter

if len(sys.argv) != 2:
	print ("Usage: plotUtil.py <Log_file.out>")
	exit(-1)

logFile = sys.argv[1];

N = []
elapsedTime = []
startupTime = 0.0

with open(logFile, 'r') as logFile:
	for line in performanceLogFile:
		vals = line.split(',')

		N.append(int(vals[0]))
		elapsedTime.append(float(vals[-1]))
		startupTime = float(vals[-2])

print (N)
print (elapsedTime)
print (startupTime)
exit(0)

ax.plot(numAdditions, kernelAPerformance, 'r', label='Performance (Kernel A)', linewidth=2.0)
ax.set_xlabel('Number of add operations')
ax.set_ylabel('Performance (GFlops)')
plt.savefig('./Task0' + str(task) + '_KernelA_Performance.png', dpi=300)

fig, ax = plt.subplots()
ax.set_title('Bandwidth (Kernel M) - Occupancy: ' + occupancy[task-2])

ax.plot(numMemoryOperations, kernelMBandwidth, 'r', label='Bandwidth (Kernel M)', linewidth=2.0)
ax.set_xlabel('Number of memory operations')
ax.set_ylabel('Bandwidth (GB/s)')
plt.savefig('./Task0' + str(task) + '_KernelM_Bandwidth.png', dpi=300)
