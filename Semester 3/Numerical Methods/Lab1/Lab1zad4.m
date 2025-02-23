clc
clear all
close all

[x,y]=meshgrid([-500:1:500],[-500:1:500]);
%f = @(x,y) x.^2+y.^2;
f= @(x,y) -x.*sin(sqrt(abs(x)))+ (-y.*sin(sqrt(abs(y))));
w=f(x,y);
figure
mesh(x,y,w)
title("2.7 Schwefel's function 7")
