
[x,y]=meshgrid([-10:0.5:10],[-10:0.5:10]);

f = @(x,y) x.^2+y.^2;
w=f(x,y);

figure
subplot(2,2,1)
plot3(x,y,w,'r.')

subplot(2,2,2)
mesh(x,y,w)

subplot(2,2,3)
surf(x,y,w)

subplot(2,2,4)
surfl(x,y,w)