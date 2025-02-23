clc
clear all
close all
% a d c
h = 0.0001;
tol = 10^(-5);

% Funkcja 1
f= @(x) x.^2-2;
a = 1/4;
b= 3/4;
x = a:h:b;

% Funkcja 2
% f = @(x) ((1/3)*x.^2) - ((13/7)*x) + 11;
% a = -10;
% b = 10;
% x = a:h:b;

% Funckja 3
% f = @(x) x.^4 - 12.*x.^3+ x + 4;
% a = -2;
% b = 2;
% x = a:h:b;

% Funkcja 4
% f = @(x) -x.^3 + 3*x.^2 - 3*x;
% a = -2;
% b = -1;
% x = a:h:b;

% Funkcja wlasna
% f = @(x) 3*x.^5+8*x.^2-2*x+3*x+1;
% a = -0.5;
% b =1;
% x = a:h:b;


df = @(x) (f(x+h)-f(x-h))/(2*h);
d2f = @(x) (f(x+h)-(2*f(x))+f(x-h))/(h^2);

% Metoda Polowienia
subplot(3,1,1)
MetodaPolowienia(f,x,a,b,tol);

% Metoda Davidona
subplot(3,1,2)
MetodaDavidona(f,a,b,x,df,tol);

% Metoda Powella
subplot(3,1,3)
MetodaPowella(f,a,b,x,df,tol);