%NxN matrix
N=151;

b=zeros(N^2,1);
b(round(N^2/2),1)=-100;

A=tridiag(N);

V=A\b;
S=vecreform(V,N);
surf(S);
