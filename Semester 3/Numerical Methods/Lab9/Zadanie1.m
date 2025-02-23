clear all 
close all
clc

a = 1;
e = [1 0; 0 1; -1 0; 0 -1];
e = e';
x1 = -10;
x2 = 10;
y1 = -10;
y2 = 10;
[x,y] = meshgrid([x1:a:x2],[y1:a:y2]);
% ps =[rand(1)*20-10; rand(1)*20-10];
ps=[-4;3];
f = @(x,y) x.^2 + y.^2 +x*y;
iter = 0;
punkty = [];
punkty = [punkty ps];
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

fe1 = f(e1(1),e1(2));
fe2 = f(e2(1),e2(2));
fe3 = f(e3(1),e3(2));
fe4 = f(e4(1),e4(2));
w = [fe1,fe2,fe3,fe4, f(px,py)];
if(min(w) == fe1) 
    ps =e1; 
elseif (min(w) == fe2) 
    ps = e2; 
elseif (min(w) == fe3) 
    ps = e3;
elseif (min(w) == fe4) 
    ps = e4;
else break;
end
if(iter >2000) break; end
end
toc
iter;
ps;
punkty
subplot(1,2,1)
hold on
title("Wartosc funkcji w Pmin("+ps(1)+", "+ps(2)+") = " + f(ps(1),ps(2))+"  Liczba iteracji: " + iter + " Krok: " + a);
[x,y] = meshgrid([x1:0.1:x2],[y1:0.1:y2]);
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