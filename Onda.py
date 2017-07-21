
# coding: utf-8

# In[1]:

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


# In[2]:

#Ctes
c = 1
n = 300

#alfa x  = alfa y
alfa = .5
alfa2 = alfa**2

#dx = dy
dx = 30/(n-1)
dx2 = dx**2

dt = np.sqrt((alfa*dx2)/c**2)
dt2 = dt**2

#c^2*(dt^2/dx^2)
cte = c**2*dt2/dx2

tf = 60

nt = int(tf/dt)
#print(ts)


# In[20]:

#Contenedor // Mask
mask = np.ones((n, n))

ancho = 4
#Barrera completa a 1/3 de la parte inferior (está a las 2/3 partes): (2*300/3 = 200) (ancho +-4)
mask[int(2*n/3-ancho) : int(2*n/3+ancho)] = 0

interval = np.arange(int(n/2-ancho),int(n/2+ancho), dtype=int)
#print(interval)

for i in interval:
    mask[int(2*n/3-ancho)  : int(2*n/3+ancho), i] = 1


# In[23]:

#plt.imshow(mask, cmap = 'GnBu')
#plt.show()


# In[24]:

#Cond inicial

#Todos 0
u0 = np.zeros((n, n))

#Excepto donde esta la perturbacion 1/3 desde borde superior y en la mitad
u0[int(n/3), int(n/2)] = -0.5

#print(ini[99])


# In[25]:

u1 = u0.copy()

U = [u0, u1]


# In[26]:

# ODE onda en 2Dim
for k in range(1, nt-1):
    u = np.zeros((n, n))
    for i in range(1, n-1):
        for j in range(1, n-1):
            teorico = 2*U[k][i, j] - U[k-1][i, j] + cte*(U[k][i, j-1] - 2*U[k][i, j] + U[k][i, j+1]) + cte*(U[k][i+1, j] -2*U[k][i, j] + U[k][i-1, j])
            u[i, j] = teorico*mask[i, j]

    U.append(u)


# In[ ]:

#Para lo de la "profundidad"

for i in range(nt):
    U[i] = U[i] + 2


# In[ ]:

#graficas y animaciones
fig = plt.figure()

grafica = plt.imshow(U[-1], cmap="GnBu")
plt.colorbar(grafica).set_label("Profundidad")

plt.imshow(mask, alpha = 0.3, cmap="GnBu")


def animate(i):
    grafica.set_array(U[i])
    if i == int(len(U)/2):
        plt.savefig("ondaent30.png")
    elif i == len(U) -1:
        plt.savefig("ondaent60.png")
    return grafica,

ani = animation.FuncAnimation(fig, animate, frames = nt)
ani.save("Onda.mp4")