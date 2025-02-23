clear all
close all
clc
% syms x y;
lambda = 0.1;
h =0.01;
x1 = -10;
y1 = -10;
x2 = 10;
y2 = 10;
[x,y]=meshgrid([x1:lambda:x2],[y1:lambda:y2]);
pk = [-4;9];
p0 = pk;
f = @(x,y) (x+2).^2 + (y+3).^2 + x * y;
% f = @(x,y) x.^2 + y.^2 + x*y;
dx = @(x, y) (f(x+h, y)-f(x, y))/h;
dy = @(x, y) (f(x, y+h)-f(x, y))/h;
d2x = @(x, y) (f(x+h, y)-2*f(x, y)+f(x-h, y))/(h^2);
d2y = @(x, y) (f(x, y+h)-2*f(x, y)+f(x, y-h))/(h^2);
dxy = @(x, y) (f(x+h, y+h) - f(x+h, y-h) - f(x-h, y+h) + f(x-h, y-h))/(4*h^2);
% grad = [dx; dy];
% H = [diff(f,x,2), diff(dfx,y,1); diff(dfy,x,1), diff(f,y,2)];
% H = H^-1;
iter = 0;
tol = 0.01;
punkty = [];
punkty = [punkty pk];
tic
for i=1:100
    t = p0;
    p0 = pk;
    grad = [dx(pk(1, 1), pk(2, 1)); dy(pk(1, 1), pk(2, 1))];
    H = [d2x(pk(1, 1), pk(2, 1)), dxy(pk(1, 1), pk(2, 1)); dxy(pk(1, 1), pk(2, 1)), d2y(pk(1, 1), pk(2, 1))];
    H = H^-1;
    pk = p0 - H*grad;
    punkty = [punkty pk];
    iter = iter +1;
    if(pk == [0; 0])
        break;
    end
    if((abs(f(pk(1, 1), pk(2,1))-f(p0(1, 1), p0(2,1)))<tol))
        break;
    end
    if(abs(f(pk(1, 1), pk(2,1))-f(t(1, 1), t(2,1)))==0)
        break;
    end
end
Pmin = pk;
toc
subplot(1, 2, 1)
hold on
title("Wartosc funkcji w Pmin("+pk(1)+", "+pk(2)+") = " + f(pk(1),pk(2))+"  Liczba iteracji: " + iter);
[x,y] = meshgrid([x1:0.01:x2],[y1:0.01:y2]);
contour(x,y, f(x,y))
axis("square")
plot(punkty(1,1),punkty(2,1),"ko");
text(punkty(1,1)+0.2,punkty(2,1)+0.2,"Ps")
plot(pk(1),pk(2),"go");
text(pk(1)+0.2,pk(2)+0.2,"Pmin")
for i=2:length(punkty)
    if(i<length(punkty))plot(punkty(1,i),punkty(2,i),"r.");end
    line([punkty(1,i-1),punkty(1,i)],[punkty(2,i-1),punkty(2,i)])
end
hold off
subplot(1, 2, 2)
[x,y]=meshgrid([x1:0.5:x2],[y1:0.5:y2]);
surf(x, y, f(x, y))
axis("square")
title("Wykres funkcji f(x, y) = (x+2).^2 + (y+3).^2 + x * y");
