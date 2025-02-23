clc 
clear all
close all
x1 = linspace(-1,1,3);
x1 = x1';
x2 = linspace(-1,1,15);
x2 = x2';
x3 = linspace(-1,1,30);
x3 = x3';
x4 = linspace(-1,1,45);
x4 = x4';
f = @(x) 1./(25*x.^2+1);

V1 = zeros(length(x1));
for i=1:length(x1)
    V1(:,i) = x1.^(i-1);
end
V1 = fliplr(V1);
a1=(V1^-1)*f(x1);
h1 = Horner(a1,x1);

V2 = zeros(length(x2));
for i=1:length(x2)
    V2(:,i) = x2.^(i-1);
end
V2 = fliplr(V2);
a2=(V2^-1)*f(x2);
h2 = Horner(a2,x2);

V3 = zeros(length(x3));
for i=1:length(x3)
    V3(:,i) = x3.^(i-1);
end
V3 = fliplr(V3);
a3=(V3^-1)*f(x3);
h3 = Horner(a3,x3);

V4 = zeros(length(x4));
for i=1:length(x4)
    V4(:,i) = x4.^(i-1);
end
V4 = fliplr(V4);
a4=(V4^-1)*f(x4);
h4 = Horner(a4,x4);

subplot(2,2,1)
hold on
title("Liczba wezlow 3");
plot(x1,f(x1),"r")
plot(x1,h1, "go")
hold off

subplot(2,2,2)
hold on
title("Liczba wezlow 15");
plot(x2,f(x2),"r")
plot(x2,h2, "go")
hold off

subplot(2,2,3)
hold on
title("Liczba wezlow 30");
plot(x3,f(x3),"r")
plot(x3,h3, "go")
hold off

subplot(2,2,4)
hold on
title("Liczba wezlow 45");
plot(x4,f(x4),"r")
plot(x4,h4, "go")
hold off