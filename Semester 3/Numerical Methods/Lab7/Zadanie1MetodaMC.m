%METODA MONTE CARLO
clc
clear all
close all
x1 = [5,10,12,20,25,35,40,50,60,65,73,85,90,100,110,120,135,150,155,165];
y1 = [0,7,10,16,20,25,26,29,30,30,40,45,30,20,13,10,5,12,25,0];
x2 = [5,10,18,30,35,45,50,56,70,90,100,110,120,135,140,150,155,165];
y2 = [0,-6,-11,-15,-25,-30,-23,-21,-22,-20,-19,-17,-12,-5,-6,-10,-20,0];
length(x1);
length(y1);
Xq = 5:0.001:165;
Vq1m = interp1(x1,y1,Xq,"makima"); 
Vq2m = interp1(x2,y2,Xq,"makima");
hold on 
title("Metoda Monte Carlo | liczba strzalow = 500")
plot(x1,y1,'bo',Xq,Vq1m,"b")
plot(x2,y2,'bo',Xq,Vq2m,"b")
k = max(interp1(x1,y1,Xq,"makima"));
l = min(interp1(x2,y2,Xq,"makima"));
line([5,165],[0,0])
line([5,5],[l,k])
line([165,165],[l,k])
line([5,165],[l,l])
line([5,165],[k,k])

strzaly = 500;
celne = 0;
chybione = 0;
for i=1:1:(strzaly/2)
    xsgora = 5+rand()*160;
    ysgora = rand()*k;
    xsdol = 5+rand()*160;
    ysdol = rand()*l;
    if(ysgora <= interp1(x1,y1,xsgora,"makima"))
        plot(xsgora,ysgora,"g.")
        celne = celne +1;
    else
        plot(xsgora,ysgora,"r.")
        chybione = chybione +1;
    end
    if(ysdol >= interp1(x2,y2,xsdol,"makima"))
        plot(xsdol,ysdol,"g.")
        celne = celne +1;
    else
        plot(xsdol,ysdol,"r.")
        chybione = chybione +1;
    end
end
poleryby = (celne/strzaly)*(160*(k+(abs(l))))
hold off