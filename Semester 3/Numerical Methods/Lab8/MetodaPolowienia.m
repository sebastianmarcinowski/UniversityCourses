function [xm] = MetodaPolowienia(f,x,a,b,tol)
% a - Metoda Poławiania
xm = (a+b)/2;
iter = 1;
v = [xm];
tic
while (abs(b-a)>tol)
    xm = (a+b)/2;
    L=b-a;
    x1 =a+(0.25*L);
    x2=b-(0.25*L);
    w = [f(a),f(x1),f(xm),f(x2),f(b)];
    w(w==max(w))=[];
    w(w==max(w))=[];
    a = x(f(x)==min(w));
    b = x(f(x)==max(w));
    iter = iter +1;
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
    plot(v(i),f(v(i)),'bo');
end
title("Metoda Polowienia | xm = " + xm + " liczba iteracji: " + iter)
plot(xm,f(xm),'ro');
plot(x,f(x),'g');
hold off