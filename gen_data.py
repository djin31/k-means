import random
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from mpl_toolkits import mplot3d
import sys
import numpy as np

dataset = []
k = int(sys.argv[1] )

point_per_cluster=2000
coord_range = 1000
dev_range = 200

points = set()

fig = plt.figure()
ax = fig.gca(projection='3d')
colors = cm.rainbow(np.linspace(0, 1, k))

f = open("test" + str(k) + ".txt","w")
g = open("solution" + str(k) +".txt","w")
for i in range(k):
	x,y,z = random.randint(-coord_range,coord_range), random.randint(-coord_range,coord_range), random.randint(-coord_range,coord_range)
	cluster_size=0

	x_l = []
	y_l = []
	z_l = []

	while(cluster_size<point_per_cluster):
		p_x,p_y,p_z = x+random.randint(-dev_range,dev_range), y+random.randint(-dev_range,dev_range), z+random.randint(-dev_range,dev_range)
		if (p_x,p_y,p_z) not in points:
			points.add((p_x,p_y,p_z))
			cluster_size+=1
			x_l.append(p_x)
			y_l.append(p_y)
			z_l.append(p_z)
	ax.scatter(x_l,y_l,z_l,color=colors[i])


f.write("%d %d\n"%(len(points), k))
for i in points:
	f.write("%d %d %d\n" %(i[0],i[1],i[2]))
f.close()

plt.show()
plt.savefig("testplot.jpg")