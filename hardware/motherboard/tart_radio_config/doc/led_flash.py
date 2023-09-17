
import numpy as np
import matplotlib.pyplot as plt 

pi = 3.14159;

def qsin(x):
    if x < 0:
        return -qsin(-x)
    
    pis = pi*pi
    px = (pi - x);
    xpx = x*px;
    y = (16*xpx)/(5*pis - 4*xpx);
    return y


jarray = np.linspace(-128, 128, 256)
theta = [((float)(j) / 128.0) * 3.14159265 for j in jarray]
sarray = [qsin(pi/2 - _x) for _x in theta]

yarray = (np.array(sarray)+1.0)/2;

plt.plot(theta,yarray)
# plt.plot(theta,sarray)
plt.show()
