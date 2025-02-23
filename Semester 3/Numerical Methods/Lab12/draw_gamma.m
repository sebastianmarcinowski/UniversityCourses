clc
clear all
close all


x = [0,0.25,0.5,0.75,1];
y = [2.05,17.6,74.5,169,295];

% subplot(1,2,1)
figure
plot(x,y)
xlabel("Luma (kolor piksela")
ylabel("Luminacja wyświetlacza [cd/m2]")

for i=1:length(y)
    y(i) = y(i)/295;
end
% subplot(1,2,2)
figure
hold on
plot(x,y)
xlabel("Luma (kolor piksela")
ylabel("Znormalizowana luminacja wyświetlacza")

y = x.^1.9712;
plot(x,y,"r")

y = y.^(1/1.19712);
plot(x,y,Color='red',LineStyle="--")
hold off
% curveFitter(x,y)

y = [2.45,76,150,229,301];
for i=1:length(y)
    y(i) = y(i)/301;
end
figure
plot(x,y)

