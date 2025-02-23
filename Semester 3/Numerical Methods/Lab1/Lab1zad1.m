clc %czysci okno
close all %zamyka otwarte okna
clear all %czysci wartości zmienne w workspace
% %% - 2 znaki procenty pozwalaja na wykonanie wybranego bloku kodu

c=[1 2 3 4];
g=[1 2 3 4];

x = 1:0.1:10;
y = sin(x);
z = cos(x);

%wektory na 1 ukladzie wspolrzednych
%sposob 1
%hold on 
%plot(x,y, color = 'red')
%plot(x,z, color ='yellow')
%hold off

%sposob 2
%figure
%plot(x,y,'r',x,z,'b')

% 2 wektory obok siebie
% wartosci w subplot definiuja jak ulozone beda wykresy wzgledem siebie
%figure
%subplot(2,3,1)
%plot(x,y, color='blue', marker='+', LineStyle='--')
%subplot(2,3,5)
%plot(x,z, color='red')


% wektory w osobnych oknach
figure
plot(y,x, color='blue', marker='+', LineStyle='--')
title('Wykres y(x)')
legend('legenda')
figure
plot(x,y, color='red')
title('Wykres x(y)')
%legend('legenda')

