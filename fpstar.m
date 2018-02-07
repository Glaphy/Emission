%NxN matrix
N=81;

b=zeros(N^2,1);
b(1:N,1)=100;
%b(round(N^2/2),1)=-100;

A=tridiag(N);
A(1:N,:)=0;
A(1:N,1:N)=diag(ones(N,1));


V=A\b;
S=vecreform(V,N);
surf(S);