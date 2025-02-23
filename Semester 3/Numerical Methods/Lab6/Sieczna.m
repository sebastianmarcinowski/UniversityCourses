function [x_s,n_s,czas_s] = Sieczna(f,a,b,tol,ftol)
if(f(a)*f(b)>=0)
    disp("Nie da się określić czy przedział izolacji pierwiastka istnieje")
    return
else
    tic
    z = a:tol:b;
    h = 0.001;
    d2f = @(x) (f(x-h)-2*f(x)+f(x+h))/(h^2);
    blad = 1;
    x1 = a;
    x0 = b;
    n_s =0;
    if(sign(f(a))==sign(d2f(a)))
        x0 = a;
        x1=b;
    elseif(sign(f(b))==sign(d2f(b)))
        x0=b;
        x1=a;
    end
    xi1 = x1 - f(x1)*((x1-x0)/(f(x1)-f(x0)));
    while(blad>ftol && abs(xi1-x1)>tol)
        blad = abs(f(xi1));
        x0 = x1;
        x1 = xi1;
        xi1 = x1 - f(x1)*((x1-x0)/(f(x1)-f(x0)));
        n_s = n_s +1;
    end
    x_s = xi1;
end
toc
czas_s = tic -toc;
n_s
x_s
hold on
title("Metoda siecznych")
plot(x_s,f(x_s),"ro")
plot(z,f(z),"g")
hold off