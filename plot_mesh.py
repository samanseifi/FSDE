import netCDF4
import numpy as np

import sys

from matplotlib.patches import Polygon
from matplotlib.collections import PatchCollection
import matplotlib.pyplot as plt
import matplotlib

nc = netCDF4.Dataset('2.g')

XY = nc.variables['coord']
X = XY[0][:]
Y = XY[1][:]

connect = nc.variables['connect1']

xy = np.array([X[:], Y[:]]).T

patches = []
centers = []
for coords in xy[connect[:]-1]:
    quad = Polygon(coords, True)
    patches.append(quad)
    center = sum(coords)/4
    centers.append(center)

fig, ax = plt.subplots()
colors = 100 * np.random.rand(len(patches))
p = PatchCollection(patches, cmap=matplotlib.cm.coolwarm, alpha=0.5, edgecolor='k')
p.set_array(np.array(colors))
ax.add_collection(p)
ax.set_xlim([min(X), max(X)])
ax.set_ylim([min(Y), max(Y)])
ax.set_aspect('equal')

# showing the nodal points
nodes = plt.plot(X, Y, 'k.', markersize=5)[0]
nodes.set_clip_on(False)

# showing the nodal numbers on the mesh
#if sys.argv[1]='node':
i = 1
for xy_c in zip(X,Y):
    ax.annotate(i, xy=xy_c, fontsize=8)
    i += 1

# showing the element numbers on the mesh
#if sys.argv[2]='element':
j = 1
for xy_c in centers:
    ax.annotate(j, xy=xy_c, color='b', fontsize=8)
    j += 1


plt.savefig('mesh.pdf', dpi=200)
plt.show()
