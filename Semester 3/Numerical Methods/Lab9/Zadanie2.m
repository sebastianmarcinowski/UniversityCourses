clear all 
close all
clc

a = 0.01;
e = [1 0; 0 1; -1 0; 0 -1; 1/sqrt(2) 1/sqrt(2); -1/sqrt(2) 1/sqrt(2); 1/sqrt(2) -1/sqrt(2); -1/sqrt(2) -1/sqrt(2)];
e = e';
x1 = -10;
x2 = 10;
y1 = -10;
y2 = 10;
[x,y] = meshgrid([x1:a:x2],[y1:a:y2]);
% ps =[rand(1)*10-5; rand(1)*16-8];
ps = [-4;3];
% f = @(x,y) (x+2).^2 + (y+3).^2 + x * y;
f = @(x,y) x.^2 + y.^2 + x*y;
iter = 0;
punkty = [];
punkty = [punkty ps];
tol = 0.01;
tic
while(1)
iter = iter +1;
px = ps(1);
py = ps(2);
punkty = [punkty ps];
e1 = ps + a*e(:,1);
e2 = ps + a*e(:,2);
e3 = ps + a*e(:,3);
e4 = ps + a*e(:,4);
e5 = ps + a*e(:,5);
e6 = ps + a*e(:,6);
e7 = ps + a*e(:,7);
e8 = ps + a*e(:,8);

fe1 = f(e1(1),e1(2));
fe2 = f(e2(1),e2(2));
fe3 = f(e3(1),e3(2));
fe4 = f(e4(1),e4(2));
fe5 = f(e5(1),e5(2));
fe6 = f(e6(1),e6(2));
fe7 = f(e7(1),e7(2));
fe8 = f(e8(1),e8(2));
w = [fe1,fe2,fe3,fe4,fe5,fe6,fe7,fe8, f(px,py)];
% w = [fe1,fe2,fe3,fe4, f(px,py)];
if(min(w) == fe1) 
    ps =e1; 
elseif (min(w) == fe2) 
    ps = e2; 
elseif (min(w) == fe3) 
    ps = e3;
elseif (min(w) == fe4) 
    ps = e4;
elseif (min(w) == fe5) 
    ps = e5;
elseif (min(w) == fe6) 
    ps = e6;
elseif (min(w) == fe7) 
    ps = e7;
elseif (min(w) == fe8) 
    ps = e8;
% else a = a/2;
else break;
end
if(iter >2000) break; end
end
toc
iter;
ps;
punkty;
subplot(1,2,1)
hold on
title("Wartosc funkcji w Pmin("+ps(1)+", "+ps(2)+") = " + f(ps(1),ps(2))+"  Liczba iteracji: " + iter);
[x,y] = meshgrid([x1:0.01:x2],[y1:0.01:y2]);
contour(x,y, f(x,y))
axis("square")
plot(punkty(1,1),punkty(2,1),"ko");
text(punkty(1,1)+0.2,punkty(2,1)+0.2,"Ps")
plot(ps(1),ps(2),"go");
text(ps(1)+0.2,ps(2)+0.2,"Pmin")
for i=2:length(punkty)
    if(i<length(punkty))plot(punkty(1,i),punkty(2,i),"r.");end
    line([punkty(1,i-1),punkty(1,i)],[punkty(2,i-1),punkty(2,i)])
end
hold off
subplot(1,2,2)
[x,y] = meshgrid([x1:0.5:x2],[y1:0.5:y2]);
surf(x,y,f(x,y))
axis("square")