inputmatrix = [100 100 100 100 100;
                0   8   8   8   0;
                0   8   8   8 	0;
                0   8   8   8   0;
                0   0   0   0   0]; %NxN matrix
            
N = length(inputmatrix);
n = N^2 - 4

%8 stands for unknown
solvematrix = zeros(n,n);
solvevector = zeros(n,1); %A\b to solve Ax = b for x
c = 1;

for i = [1:N]
    for j = [1:N]
        if (i==1 && j==1) || (i==1 && j==N) || (i==N && j==1) || (i==N && j==N)
        c = c - 1;
            
        elseif inputmatrix(i,j) ~= 8 %i.e. if it is known
            solvematrix(c,c) = 1;
            solvevector(c,1) = inputmatrix(i,j);
        elseif c <= round(n/2)
            solvematrix(c,c-3:c+2) = [1 0 0 4 0 1];
        else
            solvematrix(c,c-2:c+3) = [1 0 4 0 0 1];
        end
        c = c + 1;
    end
end

solution = solvematrix\solvevector;
solution'
