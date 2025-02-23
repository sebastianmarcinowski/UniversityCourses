clc
clear all
close all
% Metoda a i c
f = @(x) sin(x);
a = -1;
b = 1;
ftol = 10^(-4);
tol = 10^(-5);

% Metoda a -> metoda bisekcji(połowienia)
subplot(1,2,1)
Bisekcja(f,a,b,tol,ftol);

% Metoda c -> metoda siecznych
subplot(1,2,2)
Sieczna(f,a,b,tol,ftol);
