function [A,B,F,Z,Wb] = OpcjeRozszerzenia(A,B,F,Z)

%opcja 1
n = numel(B); 
w = numel(A(1, :));
for i=1:n
    if(B(i)<0)
       A(i, 1) = A(i, 1)*(-1);
       A(i, 2) = A(i, 2)*(-1);
       B(i) = B(i)*(-1);
       Z(i) = Z(i)*(-1);
    end
end
%opcja 2
for i=1:n 
    if(Z(i)==1)
        A(:, (w+i)) = 0;
        F(w+i) = 0;
        A(i, (w+i)) = -1;
    elseif(Z(i)==-1)
        A(:, (w+i)) = 0;
        F(w+i) = 0;
        A(i, (w+i)) = 1;
    end
    Z(i) = 0;
end
%opcja 3
w2 = numel(A(1, :))+1; 
for i=1:n
    if(all(A(i, w+1:end) ~= 1))
        A(:, w2) = 0;
        F(w2) = -1000000;
        A(i, w2) = 1;
        w2 = w2+1;
    end
end
a = 0;
for i=numel(A(1, :))-w:numel(A(1, :))
    if(any(A(:, i) == 1)) 
        a = a +1;
    end
end
%opcja 4
for i=1:a 
    Wb(i) = w+find(A(i, w+1:end)==1);
end