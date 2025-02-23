clear all
close all
clc
% format("longE")
% xavier 214
% x = [0.48,0.43,0.38,0.33,0.28];
% y = [33.7003,28.794,24.5976,19.9130,17.0156];
% n = 5;
% z = x.*y;
% w = sum(z);
% x2 = x.^2;
% y2 = y.^2;
% a = (n*w-sum(x)*sum(y))/(n*sum(x2)-sum(x)^2);
% b= (sum(y)-a*sum(x))/n;
% ua = sqrt((n/(n-2))*(sum(y2)-a*w-b*sum(y))/(n*sum(x2)-sum(x)^2));
% ub = ua*sqrt((1/n)*sum(x2));
% r = (n*w-sum(x)*sum(y))/sqrt((n*sum(x2)-sum(x)^2)*(n*sum(y2)-sum(y)^2));
% hold on
% plot(x,y)

% Michal 205
% Ta = [1.19028,1.20028,1.21416];
% Tb =1.20564;
% lb = [0.365,0.355,0.345];
% plot(lb,Ta)
% T1 =1.21416;
% T2=1.20028;
% l2 = 0.355;
% l1 = 0.365;
% t = [30.159,30.140,30.144,30.137,30.143];
% tsr = 30.141;
% a = (T2-T1)/(l2-l1);
% b = (T2*l1-T1*l2)/(l1-l2);
% lzr = (Tb-b)/a;
% g = (4*pi^2*lzr)/(Tb^2);
% ut = sqrt(((tsr-t(1))^2+(tsr-t(2))^2+(tsr-t(3))^2+(tsr-t(4))^2+(tsr-t(5))^2)/20);
% uatb = ut/25;
% dTb = 0.01/25;
% uTb = sqrt(uatb^2+((dTb/sqrt(3))^2));
% ulzr = uTb/a;
% ug = g * sqrt((ulzr/lzr)^2+((2*uTb)/Tb)^2);

% Xavier 206
g = 9.807;
n =10;
deltam = 0.00002;
detlat = 0.25;
deltad = 0.0001;
% Tarcza
m = 1.8658;
r = 0.124;
l=2*r;
d = 0.1024;
t = [8.38,6.34,6.5];
tsr = 8.4;
T = tsr/n
I0 = (m*r^2)/2
I = (T^2*m*g*d)/(4*pi^2)
Io1 = I - m*d^2

% Kula
m = 1.979;
r=0.0394;
l=2*r;
d=0.0514;
t=[5.03,5.31,5.07];
tsr = 5.14;
I0 = (2/5)*(m*r^2)
T = tsr/n
I = (T^2*m*g*d)/(4*pi^2)
Io1 = I - m*d^2

% Pret
m = 0.707;
r = 0.810;
l = r;
d=0.398;
t =[14.5,14.31,14.69];
tsr = 14.5;
I0 = (m*r^2)/12
T = tsr/n
I = (T^2*m*g*d)/(4*pi^2)
Io1 = I - m*d^2

um = (deltam*m)/sqrt(3);
ud = (deltad*d)/sqrt(3);
ub1t = (0.25/sqrt(3))/10;
ub2t = (0.4/sqrt(3))/10;
uat = (sqrt(((t(1)-tsr)^2+(t(2)-tsr)^2+(t(3)-tsr)^2)/6))/10;
ut = sqrt(ub1t^2 + ub2t^2 + uat^2);
uI = I * sqrt(((2*ut)/T)^2+((2*um)/m)^2+((2*ud)/d)^2);
uI01 = sqrt(uI^2 + (d^2*um)^2 + (2*m*d*ud)^2);
ubr = (deltam*r)/sqrt(3);
ubl = (deltam*l)/sqrt(3);
ur = sqrt(ubr^2);
ul = sqrt(ubl^2);
uI0 = I0 * sqrt((um/2)^2 + ((2*ul)/l)^2);
