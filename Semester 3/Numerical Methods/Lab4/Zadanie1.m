clc
clear all
close all
format("default")
n = 5000;
A = rand(n);
B = rand(n);
E = eye(n);
x = ones(n,1);
d = rand(n,1);
c = rand(n,1);

tic
iterP(A,d,n)
toc

tic
eliminGC(B,c,n)
toc

wIter = [0.007802,0.010752,0.010637,0.013288,0.028059,0.084904,0.212639,0.347282];
wGaus = [0.005808,0.011290,0.028755,0.201711,3.092289,56.277035,214.795995,873.610447];
wielkosc = [10,100,200,500,1000,2000,3000,5000];

subplot(2,1,1)
plot(wielkosc,wIter)
title("Metoda iteracji prostej")
subplot(2,1,2)
plot(wielkosc,wGaus)
title("Metoda Gaussa-Crouta")