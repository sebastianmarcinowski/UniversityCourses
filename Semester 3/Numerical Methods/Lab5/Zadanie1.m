clear all
clc
close all

x1 = [5,10,12,20,25,35,40,50,60,65,73,85,90,100,110,120,135,150,155,165];
y1 = [0,7,10,16,20,25,26,29,30,30,40,45,30,20,13,10,5,12,25,0];
x2 = [5,10,18,30,35,45,50,56,70,90,100,110,120,135,140,150,155,165];
y2 = [0,-6,-11,-15,-25,-30,-23,-21,-22,-20,-19,-17,-12,-5,-6,-10,-20,0];
length(x1);
length(y1);
Xq = 5:1:165;
Vq1p = interp1(x1,y1,Xq,"pchip"); 
Vq2p = interp1(x2,y2,Xq,"pchip");
subplot(2,2,1)
title("Pchip")
hold on
plot(x1,y1,'or',Xq,Vq1p,"b")
plot(x2,y2,'or',Xq,Vq2p,"b")
hold off

Vq1l = interp1(x1,y1,Xq,"linear"); 
Vq2l = interp1(x2,y2,Xq,"linear");
subplot(2,2,2)
title("Linear")
hold on 
plot(x1,y1,'or',Xq,Vq1l,"b")
plot(x2,y2,'or',Xq,Vq2l,"b")
hold off

Vq1s = interp1(x1,y1,Xq,"spline"); 
Vq2s = interp1(x2,y2,Xq,"spline");
subplot(2,2,3)
title("Spline")
hold on 
plot(x1,y1,'or',Xq,Vq1s,"b")
plot(x2,y2,'or',Xq,Vq2s,"b")
hold off

Vq1m = interp1(x1,y1,Xq,"makima"); 
Vq2m = interp1(x2,y2,Xq,"makima");
subplot(2,2,4)
title("Makima")
hold on 
plot(x1,y1,'or',Xq,Vq1m,"b")
plot(x2,y2,'or',Xq,Vq2m,"b")
hold off