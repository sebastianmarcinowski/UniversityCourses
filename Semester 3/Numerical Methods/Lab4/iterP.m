function [X] = iterP(A,b,n)
WZ = [A b];
for i=1:length(A)
  WZ(i,:) = WZ(i,:) / WZ(i,i);
  WZ(i,i) = 0;
end
W = WZ(:,1:1:n);
W = W*(-1);
Z=WZ(:,n+1);
X = zeros(n,1);
iteracje = 0;
for i=1:100
    V = X;
    X = W*X+Z;
    Y(:,i) = X;
    d = max(abs(X-V));
    if(d<0.01)
        iteracje = i
    break;
    end
end
end

