clc
clear all
close all

% Przyklad ->podstawa
% A = [2 1 1 0 0; 3 3 0 1 0; 2 0 0 0 1];
% B = [10; 24; 8];
% Z = [-1; -1; -1];
% F = [300, 200, 0, 0, 0];
% Wb = [3, 4, 5];

% Przyklad ->rozszerzenie
A = [-2 -1; 3 3; 2 0];
B = [-10; 24; 8];
Z = [-1; -1; 0];
F = [300, 200];

% OPCJE
%---------------------------------------------- 
[A,B,F,Z,Wb] = OpcjeRozszerzenia(A,B,F,Z);
%----------------------------------------------


[w,k] = size(A);
flaga = false;
Cb = F(Wb);
while(flaga == false)
    F0 = Cb * B;
    for j=1:numel(A(1,:))
        WW(1,j) = Cb*A(:,j)-F(j);
    end

    %wypisanie tablicy
    tablica=[];
    tablica(1,:) = [0,0,0, F];
    for i=1:length(Z)
        wiersz = [Cb(i),B(i),Wb(i)];
        for j=1:k
            wiersz = [wiersz A(i,j)];
        end
        tablica(i+1,:) = wiersz;
        wiersz =[];
    end
    tablica(length(Z)+2,:) = [0,0,F0, WW];
    format shortg
    tablica

    if(all(WW>=0))
        display('To jest ostatnia tablica');
        display("Maksymalna wartość funkcji celu wynosi: "+F0+" dla x1="+B(find(Wb==1))+", x2="+B(find(Wb==2)));
        flaga = true;
    else
        display("To nie jest ostatnia tablica");
        [minWW1, minWW2] = min(WW);
        KK = A(:, minWW2);
        for i=1:numel(A(:, minWW2))
          if(A(i, minWW2)>0)
              WP(i) = B(i)/A(i, minWW2);
          else
              WP(i) = 1000000000;
          end
        end
        [minWP1, minWP2] = min(WP);
        WK = A(minWP2, :);
        ER = A(minWP2, minWW2);
        Wb(minWP2) = minWW2;
        Cb(minWP2) = F(minWW2);
        WK = WK./ER;
        A(minWP2, :) = WK;
        B(minWP2) = B(minWP2)/ER;
        for i=1:numel(A(:, 1))
            if(i ~= minWP2)
                B(i) = B(i) - A(i, minWW2)*B(minWP2);
                A(i, :) = A(i, :) - A(i, minWW2)*WK;
            end
        end
    end
end