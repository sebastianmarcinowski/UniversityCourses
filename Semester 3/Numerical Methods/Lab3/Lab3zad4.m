clc 
clear all
close all

x = 40545;
y =70226;
% y=single(y);
% x=single(x);
% x1 = int64(x)
% y1 = int64(y)
f= @(x,y) 9*x^4-y^4+2*y^2;
f2=@(x,y) (3*x^2-y^2+1)*(3*x^2+y^2-1)+1;
v=f(x,y);
v