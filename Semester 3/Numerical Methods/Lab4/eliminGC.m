function [] = eliminGC(A,b,n)
W = [A b];
X = zeros(n,1);
for i= 1:n
    if(W(i,i)==0)
        for j=i:n
            if(W(j,i)==max(W(:,i)))
                W([i j], :) = W([j i], :);
            end
        end
    end
end

for i=1:n
    for j=(i+1):n
        W(i,:) = W(i,:)/W(i,i);
        W(j,:) = W(j,:) - W(j,i)*W(i,:);
    end
W(n,:) = W(n,:)/W(n,n);
end
for i=1:n
X(i) = W(i,n+1);
end
for i=n:-1:1  
    for j=i+1:n
        X(i) = X(i)-W(i,j)*X(j);
    end
end
% X
% W
end