import os
import sys

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.collections import PolyCollection
from matplotlib.collections import LineCollection
from matplotlib.colors import colorConverter

if len(sys.argv) != 1:
	print ("Usage: plotUtil.py")
	exit(-1)
# task = int(sys.argv[1])

fig, ax = plt.subplots()
occupancy = ['0.5', ' 1.0', '0.5']
ax.set_title('Performance (Kernel A) - Occupancy: ' + occupancy[task-2])

numAdditions = []
numMemoryOperations = []
kernelAPerformance = []
kernelMBandwidth = []
performanceLogFilePath = os.path.join(os.getcwd(), "Output-task0" + str(task) + ".txt")
with open(performanceLogFilePath, 'r') as performanceLogFile:
	for line in performanceLogFile:
		linePortions = line.split(',')

		numAdditions.append(int(linePortions[0]))
		numMemoryOperations.append(int(linePortions[1]))

		kernelAPerformance.append(float(linePortions[-2]))
		kernelMBandwidth.append(float(linePortions[-1]))

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
