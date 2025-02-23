clc
clear all
close all
format("longE")
k=4:10;
x=10.^k
x=single(x)
a=sqrt(1+x.*x);
x=single(x)
w1 = x-a
w2=-(1./(x+a))