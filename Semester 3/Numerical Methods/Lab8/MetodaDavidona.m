function [xm] = MetodaDavidona(f,a,b,x,df,tol)
z = (3*(f(a)-f(b)))/(b-a)+df(a)+df(b);
q = sqrt(z^2-df(a)*df(b));
xm = b-((df(b)+q-z)/(df(b)-df(a)+2*q))*(b-a);
iter = 1;
v = [xm];
tic
while(abs(df(xm))>=tol)
    if(df(a)<0 && df(b)>0)
        if(df(xm)>0)
            b = xm;
        elseif(df(xm)<0)
            a = xm;
        end
    else
         break;
    end
    z = (3*(f(a)-f(b)))/(b-a)+df(a)+df(b);
    q = sqrt(z^2-df(a)*df(b));
    xm = b-((df(b)+q-z)/(df(b)-df(a)+2*q))*(b-a);
    iter = iter+1;
    v = [v xm];
end
if(xm<a)
    xm = a;
elseif(xm>b)
    xm = b;
end
toc

hold on
for i=1:length(v)
    if (v(i)>a && v(i)<b)
        plot(v(i),f(v(i)),'bo');
    end
end
title("Metoda Davidona | xm = " +xm + " liczba iteracji: " + iter);
plot(xm,f(xm),'ro')
plot(x,f(x),'g')
hold off