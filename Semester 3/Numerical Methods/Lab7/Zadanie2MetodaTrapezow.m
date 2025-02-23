clc
clear all
close all
n = [5,15,50,100];
for j=1:4
x = linspace(-pi,pi,1000);
f = @(x) sin(x);
y = f(x);
hold on
subplot(2,2,j)
plot(x,y);
line([-pi,pi],[0,0])
line([-pi,-pi],[-1,1])
line([pi,pi],[-1,1])
line([-pi,pi],[-1,-1])
line([-pi,pi],[1,1])
pole = 0;
h = (2*pi)/n(j);
k = linspace(-pi,pi,n(j));
for i=2:n(j)
    line([k(i-1),k(i-1)],[0,f(k(i-1))],'color','r')
    line([k(i),k(i)],[0,f(k(i))],'color','r')
    line([k(i-1),k(i)],[f(k(i-1)),f(k(i))],'color','r') 
    pole = pole + abs(((f(k(i-1))+f(k(i)))*h)/2);
end
% quad(f,0,pi)
pole;
title("Metoda trapezow z krokiem: "+ n(j) + " Wartosc pola: " + pole);
end
hold off