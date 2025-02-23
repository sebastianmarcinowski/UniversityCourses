clc
clear all
close all
format("longE")
d=10^(-3);
x=linspace(2-d,2+d,1000);
a=(x-2);
al1=a.^4;
al2=x.^4-8*x.^3+24*x.^2-32*x+16;
w=num2str(max(abs(al1-al2)));
hold on
title(w)
plot(x,al1,'k')
plot(x,al2,'y')
figure
plot(x,al1,'k')
plot(x,al2)
axis([1.9998,2.0002,-0.025*10e-13,0.025*10e-13])
title('Wycinek wykresu')
figure
plot(x,al1-al2)
title('Wykres błędu')