clear all 
close all
clc

n=2;
% ------------------------------
R = [3.46, 3.78, 3.61];
tsr = 3.62;
A1 = [1, 1 ,1.5];
Asr = 1.2;
A0 =6;
B = 0.22;
O = 0.4;
T = 1.81;
%-------------------------------
uat = sqrt(((tsr-R(1))^2+(tsr-R(2))^2+(tsr-R(3))^2)/6);
ubt = ((tsr-R(1))+(tsr-R(2))+(tsr-R(3))/sqrt(3));
ut = sqrt(uat^2+ubt^2)
uT = ut/n
uaA1 = sqrt(((Asr-A1(1))^2+(Asr-A1(2))^2+(Asr-A1(3))^2)/6);
ubA1 = ((Asr-A1(1))+(Asr-A1(2))+(Asr-A1(3)))/sqrt(3);
uaA0 = sqrt(((Asr-A0)^2+(Asr-A0)^2+(Asr-A0)^2)/6);
ubA0 = ((Asr-A0)+(Asr-A0)+(Asr-A0))/sqrt(3);
uA1 = sqrt(uaA1^2+ubA1^2);
uA0 = sqrt(uaA0^2+ubA0^2);
uO = sqrt(((uA0^2)/A0^2)+((uA1^2)/Asr^2))
uB = B*sqrt(((uO^2)/O^2)+((uT^2)/T^2))