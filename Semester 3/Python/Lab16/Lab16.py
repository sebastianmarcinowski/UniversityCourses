from scipy import ndimage, optimize, integrate, interpolate
from matplotlib.pyplot import imread,imsave,imshow,show
import numpy as np
# Zadanie1
# img = imread("I:\Python\Lab16\logo.png")
# newimg = 1 - img
# imshow(newimg)
# imsave("I:\Python\Lab16\logoN.png", newimg)

# Zadanie 2
# img = imread("I:\Python\Lab16\logo.png")
# newimg = img[:,:,0]*0.2989
# newimg += img[:,:,1]*0.587
# newimg += img[:,:,2]*0.1196
# newimg = newimg[:140,:140]
# newimg = newimg[:,:]-(100/255)
# newimg[newimg<0]=0
# newimg = ndimage.rotate(newimg, 45)
# imshow(newimg, cmap='gray')
# imsave("I:\Python\Lab16\logo2.png", newimg)
# show()

# Zadanie 4
# def f1(x):
#     x1,x2 = x
#     return (x1+2*x2-7)**2+(2*x1+x2-5)**2
# w = optimize.minimize(f1,[-10,-10],method="Nelder-Mead",tol=1e-6)
# print(w)
# def f2(x):
#     x1,x2=x
#     return 0.5 + ((np.sin(x1**2-x2**2))**2-0.5)/((1+0.001*(x1**2+x2**2))**2)
# g = optimize.minimize(f2,[-5,5],method="Nelder-Mead",tol=1e-6)
# print(g)

# Zadanie 6
# def f1(x,y):
#     return np.e**(x+2*y)
# w = integrate.nquad(f1,[[0,1],[0,1]])
# print(w)

# def f2(x,y):
#     return (x+y**2*x)
# w = integrate.nquad(f2,[[2,3],[0,2]])
# print(w)

# def f3(x,y):
#     return (x*np.sin(x)+6*y**2)
# w = integrate.nquad(f3,[[0,np.pi],[0,2]])
# print(w)

# Zadanie 7
# def f(x):
#     return -x**4+4*x**3+2*x**2+8
# w=integrate.quad(f,-1,4)
# print(w)
# x =np.array([-1,0,1,2,3,4])
# t = integrate.trapz(f(x),x)
# print(t)
# s = integrate.simps(f(x),x)
# print(s)

# Zadanie 8
# x = [7,10,11,15,19]
# y = [7,12,13,15,13]
# w = interpolate.interp1d(x,y, kind="cubic")
# print(w(9.75))
# print(w(12.10))
# print(w(17))