
# coding: utf-8

# In[4]:

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


# In[5]:

xs = np.genfromtxt("xs.txt", skip_header=1)
ys = np.genfromtxt("ys.txt", skip_header=1)
zs = np.genfromtxt("zs.txt", skip_header=1)


# In[10]:

fig = plt.figure()
ax = fig.gca(projection='3d')

for i in range(10):
    plt.plot(xs[:, i], ys[:, i], zs[:, i], "-")

plt.xlabel("x")
plt.ylabel("y")
ax.set_zlabel("z")
#plt.show()
plt.savefig("orbitasdelosplanetas.jpg")


# In[ ]:




# In[ ]:



