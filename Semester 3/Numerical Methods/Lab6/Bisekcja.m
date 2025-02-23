function [x_b,n_b, czas_b] = Bisekcja(f,a,b,tol,ftol)
if(f(a)*f(b)>=0)
    disp("Nie da się określić czy przedział izolacji pierwiastka istnieje")
    return
else
    tic
    z = a:tol:b;
    blad = 1;
    xk = b;
    xk2 = a;
    n_b = 0;
    while (blad >= ftol && abs(xk-xk2)>=tol) 
        sr = (a+b)/2;   
        blad = abs(f(sr)); 
        n_b = n_b +1;
        if (f(a)*f(sr) < 0)
            b = sr; 
            xk = b;
            xk2 = a;
        else 
            a = sr; 
            xk = b;
            xk2 = a;
        end
    end
end
x_b = sr;
toc
czas_b = tic-toc;
n_b
x_b
hold on
title("Metoda bisekcji")
plot(z,f(z))
plot(x_b,f(x_b),"ro")
hold off