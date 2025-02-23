clear all
close all
clc

% Przyklad 1
A = [2,1; 3,3; 2,0; 1,0; 0,1];
B = [10; 24; 8; 0; 0];
F = [300,200];
Z = [-1;-1;-1;1;1];
f = @(x,y) F(1)*x + F(2)*y;

% Przyklad 2 -> brak dopuszczalnych rozwiazan
% A = [3,2 ; 4,5; 1,0; 0,1];
% B = [6; 20; 0; 0];
% F = [1,3];
% Z = [-1;1;1;1];

[wiersze,kolumny] = size(A);
n = numel(A(1, :));
% --opcja
for i=1:wiersze
   if(B(i)<0)
       A(i, 1) = A(i, 1)*(-1);
       A(i, 2) = A(i, 2)*(-1);
       B(i) = B(i)*(-1);
       Z(i) = Z(i)*(-1);
   end
end
% szukanie rozwiazan par ograniczen
temp = 1;
for i=1:wiersze
    for j=i+1:wiersze
        x = [A(i, :); A(j, :)]^(-1)*[B(i, :); B(j, :)];
        if(isinf(x(1, :))==0 && isinf(x(2, :))==0 && isnan(x(1, :))==0 && isnan(x(2, :))==0)
            rozw(1,temp) = x(1,:);
            rozw(2,temp) = x(2,:);
            temp = temp +1;
        end
    end
end
% wyłuskanie dopuszczalnych rozwiązań
temp = 1;
for i=1:numel(rozw(1,:))
    dop = true;
    for j=1:wiersze
        x = A(j,:)*rozw(:,i); %wartosc funkcji dla danego rozwiazania i wspolczynnikow ograniczen
        if(Z(j,:) == -1) %sprawdzanie znaku ograniczenia
            if(x > B(j,:)) %sprawdzanie czy wartosc spelnia ograniczenien jeśli nie zmieniam wartosc dop = false
                dop = false;
            end
        elseif(Z(j,:)==1)
            if(x < B(j,:))
                dop = false;
            end
        elseif(Z(j,:)==0)
            if(x ~= B(j,:))
                dop = false;
            end
        end
    end
    if(dop == true)
            rozwdop(1,temp) = rozw(1,i);
            rozwdop(2,temp) = rozw(2,i);
            temp = temp+1;
    end
end

if(exist('rozwdop', 'var') == 0)
    display('Brak rozwiązań dopuszczalnych');
else
% rysowanie ograniczen i kolorowanie obszaru dopuszczalnych rozwiazan
x = linspace(0, max(rozwdop(:)), 100);
y = linspace(0, max(rozwdop(:)), 100);
hold on
for i=1:wiersze
    plot(x, -A(i, 1)/A(i, 2)*x+B(i, 1)/A(i, 2), 'blue');
    if(A(i, 2)==0)
        plot(linspace(B(i, 1)/A(i, 1), B(i, 1)/A(i, 1), 100), y, 'blue')
    end
end
K = convhull(rozwdop(1,:),rozwdop(2,:));
fill(rozwdop(1,K),rozwdop(2,K), 'yellow');
% obliczanie maksymalnej wartosci
maxval = 0;
for i=1:numel(rozwdop(1,:))
    value = (rozwdop(1,i)*F(1,1) + rozwdop(2,i)*F(1,2));
    if(maxval < value)
        maxval = value;
        punkt = [rozwdop(1,i), rozwdop(2,i)];
    end
end
% zaznaczenie punktu oraz narysowanie funkcji celu ktora przez niego
% przechodzi
x2 = -F(1, 1)/F(1, 2);
y2 = punkt(1, 2) - x2 * punkt(1,1);
plot(x, x2*x+y2, 'r')
plot(punkt(1, 1), punkt(1, 2), 'or', MarkerSize=6, LineWidth=2)
title("Maksymalna wartosc funkcji celu wynosi: " + maxval + " dla x="+punkt(1,1)+", y="+punkt(1,2));
hold off
end