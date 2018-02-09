%Main Five Point Stencil

b=matreform(dlmread('chargefile.dat'));
geometry=matreform(dlmread('geometryfile.dat'));
N=sqrt(length(b));

A=tridiag(N);
A=vseek(A,geometry);

V=A\b;
S=vecreform(V,N);
surf(S);