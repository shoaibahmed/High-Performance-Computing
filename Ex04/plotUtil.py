import os
import sys

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.collections import PolyCollection
from matplotlib.collections import LineCollection
from matplotlib.colors import colorConverter

if len(sys.argv) != 3:
	print ("Usage: plotUtil.py <Same_Node_Log_file.out> <Diff_Node_Log_file.out>")
	exit(-1)

sameNodeLogFile = sys.argv[1]
diffNodeLogFile = sys.argv[2]

def loadFile(fileName):
	N = []
	elapsedTime = []
	startupTime = 0.0

	with open(fileName, 'r') as logFile:
		for line in logFile:
			vals = line.split(',')

			N.append(int(vals[0]))
			elapsedTime.append(float(vals[-1]))
			startupTime = float(vals[-2])

	# Add the zero-point
	elapsedTime = [startupTime] + elapsedTime
	N = [0] + N

	return N, elapsedTime

N_SN, elapsedTime_SN = loadFile(sameNodeLogFile)
N_DN, elapsedTime_DN = loadFile(diffNodeLogFile)

print (N_SN, elapsedTime_SN)
print (N_DN, elapsedTime_DN)

fig, ax = plt.subplots()
fig.set_size_inches(18.5, 10.5)
ax.set_title('MPI Performance Plot', color='C0')

ax.plot(N_SN, elapsedTime_SN, linestyle='--', marker='o', color='b', label='Same Node', linewidth=2.0)
ax.plot(N_DN, elapsedTime_DN, linestyle='--', marker='o', color='g', label='Different Nodes', linewidth=2.0)

ax.legend()

ax.set_xlabel('Message length (Bytes)')
ax.set_ylabel('Time (Seconds)')

outputPath = "./performancePlot.png"
plt.tight_layout()
plt.savefig(outputPath, dpi=300)
plt.show()
plt.close('all')