function [h] = Horner(a, x)
n = length(x);
h = a(1);
for i=2:n
    h = h.*x + a(i);
end
end