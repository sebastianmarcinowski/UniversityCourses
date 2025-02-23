function [T, Wx] = Zadanie3_func(X, Y, arg)
n = length(X);
% T(:,1) = X';
% T(:,2) = Y';
% Obliczanie tablicy ilorazow roznicowych
T = zeros(n-1);
for j=1:n-1
    for i =n:-1:j+1
        Y(i) = (Y(i)-Y(i-1))/(X(i)-X(i-j));
        T(i-1,j)=Y(i);
    end
end
T

% Obliczanie wartosci wielomianu
Wx =0;
for i=1:n-1
    z=1;
    for j=1:i
        z = z*(arg-X(j));
    end
    Wx = Wx + (T(i,i)*z);
end
Wx = Wx + arg;
Wx