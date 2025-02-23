clc
clear all
close all
strzaly = [100,500,1000,2000];

for j=1:4
x = -pi:0.1:pi;
f = @(x) sin(x);
y = f(x);
subplot(2,2,j)
hold on
plot(x,y);
line([-pi,pi],[0,0])
line([-pi,-pi],[-1,1])
line([pi,pi],[-1,1])
line([-pi,pi],[-1,-1])
line([-pi,pi],[1,1])
celne = 0;
chybione = 0;
% strzaly z lewej
for i=1:1:(strzaly(j)/4)
    xs = rand()*(-pi);
    ysgora = rand();
    ysdol = rand()*(-1);
    if(ysgora <= f(xs))
        plot(xs,ysgora,"g.")
        celne = celne +1;
    else
        plot(xs,ysgora,"r.")
        chybione = chybione +1;
    end
    if(ysdol >= f(xs))
        plot(xs,ysdol,"g.")
        celne = celne +1;
    else
        plot(xs,ysdol,"r.")
        chybione = chybione +1;
    end
end

% strzały z prawej
for i=1:1:(strzaly(j)/4)
    xs = rand()*(pi);
    ysgora = rand();
    ysdol = rand()*(-1);
    if(ysgora <= f(xs))
        plot(xs,ysgora,"g.")
        celne = celne +1;
    else
        plot(xs,ysgora,"r.")
        chybione = chybione +1;
    end
    if(ysdol >= f(xs))
        plot(xs,ysdol,"g.")
        celne = celne +1;
    else
        plot(xs,ysdol,"r.")
        chybione = chybione +1;
    end
end
pole = (celne/strzaly(j))*(2*pi*2);
title("Metoda Monte Carlo dla ilości strzałów: "+ strzaly(j)+ " Wartosc pola: " + pole);
end
hold off