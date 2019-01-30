#!/usr/bin/python
import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D 
import numpy
from itertools import cycle
cycol = cycle('bgrcmkyw')

f = open(sys.argv[1])

l = f.readlines()
col = next(cycol)
cluster = []
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for i in l:
	if i=="" or i=="\n":
		cluster = numpy.array(cluster, dtype=int)
		ax.scatter(cluster[:,0],cluster[:,1],cluster[:,2],c=col, marker="o")
		col = next(cycol)
		cluster = []	

	else:
		x,y,z = i.strip().split(" ")
		cluster.append([x,y,z])
plt.show()

