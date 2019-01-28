import random
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import sys

dataset = []
k = int(sys.argv[1] )
x_l = []
y_l = []
z_l = []

coord_range = 100
dev_range = 10

f = open("test" + str(k) + ".txt","w")
g = open("solution" + str(k) +".txt","w")
for i in range(k):
	x,y,z = random.randint(-coord_range,coord_range), random.randint(-coord_range,coord_range), random.randint(-coord_range,coord_range)
	n = random.randint(10,20)
	print(n)
	for i in range(n):
		p_x,p_y,p_z = random.randint(-dev_range,dev_range), random.randint(-dev_range,dev_range), random.randint(-dev_range,dev_range)
		f.write("%d %d %d\n"%(x+p_x,y+p_y,z+p_z))
		g.write("%d %d %d\n"%(x+p_x,y+p_y,z+p_z))
		x_l.append(x+p_x)
		y_l.append(y+p_y)
		z_l.append(z+p_z)
	g.write("\n")
f.close()
g.close()

fig = plt.figure()
ax = fig.gca(projection='3d')
ax.scatter(x_l,y_l,z_l,"o")
plt.show()