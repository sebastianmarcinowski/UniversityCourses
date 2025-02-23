% METODA PROSTOKATOW
clc
clear all
close all
x1 = [5,10,12,20,25,35,40,50,60,65,73,85,90,100,110,120,135,150,155,165];
y1 = [0,7,10,16,20,25,26,29,30,30,40,45,30,20,13,10,5,12,25,0];
x2 = [5,10,18,30,35,45,50,56,70,90,100,110,120,135,140,150,155,165];
y2 = [0,-6,-11,-15,-25,-30,-23,-21,-22,-20,-19,-17,-12,-5,-6,-10,-20,0];
length(x1);
length(y1);
Xq = 5:1:165;

Vq1m = interp1(x1,y1,Xq,"makima"); 
Vq2m = interp1(x2,y2,Xq,"makima");
hold on 
plot(x1,y1,'or',Xq,Vq1m,"b")
plot(x2,y2,'or',Xq,Vq2m,"b")
line([5,165],[0,0])

h = 1; %krok
pole1 = 0;
pole2 = 0;
for i=5:h:(165-h)
    line([i,i+h],[interp1(x1,y1,i+(h/2),"makima"),interp1(x1,y1,i+(h/2),"makima")])
    line([i,i],[0,interp1(x1,y1,i+(h/2),"makima")])
    line([i+h,i+h],[0,interp1(x1,y1,i+(h/2),"makima")])
    line([i,i+h],[interp1(x2,y2,i+(h/2),"makima"),interp1(x2,y2,i+(h/2),"makima")])
    line([i,i],[0,interp1(x2,y2,i+(h/2),"makima")])
    line([i+h,i+h],[0,interp1(x2,y2,i+(h/2),"makima")])
    if (i<=164)
        pole1 = pole1 + (h*interp1(x1,y1,i+(h/2),"makima"));
        pole2 = pole2 + abs(h*interp1(x2,y2,i+(h/2),"makima"));
    end
end
poleryby = pole1 + pole2
title("Metoda prostokatow | krok = " +h);
hold off