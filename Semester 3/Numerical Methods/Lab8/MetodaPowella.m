function [xm] = MetodaPowella(f,a,b,x,df,tol)
x1 = a;
x3 = b;
x2 = (x3+x1)/2;
delta = x3-x2;
xm = x2 -0.5*delta*((f(x3)-f(x1))/(f(x1)-2*f(x2)+f(x3)));
iter =1;
v = [xm];
tic
while((x3-x1)>tol || abs(df(xm)) > tol)
    if(xm<a)
        xm = a;
        break;
    elseif(xm>b)
        xm = b;
        break;
    end
    x2 = xm;
    delta = delta/2;
    x1 = x2 - delta;
    x3 = x2 + delta;
    xm = x2 -0.5*delta*((f(x3)-f(x1))/(f(x1)-2*f(x2)+f(x3)));
    iter = iter +1;
    v=[v xm];
end
toc

hold on
for i=1:length(v)
    if (v(i)>a && v(i)<b)
        plot(v(i),f(v(i)),'bo');
    end
end
title("Metoda Powella | xm = " +xm + " liczba iteracji " + iter);
plot(xm,f(xm),'ro')
plot(x,f(x),'g')
hold off