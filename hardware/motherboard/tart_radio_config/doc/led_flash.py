
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

xarray = np.linspace(-pi, pi, 100)
yarray = [qsin(_x) for _x in xarray]

plt.plot(xarray,yarray)
plt.show()
