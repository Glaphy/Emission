function A=tridiag(N)
A=zeros(N^2, N^2);
for i=[1:N^2]
	A(i,i) = -4;
	if (mod(i-1,N) ~= 0)
		A(i,i-1)=1;
	end
	if (mod(i,N) ~= 0)
		A(i,i+1)=1;
	end
	if (i<=N*(N-1))
		A(i+N,i)=1;
		A(i,i+N)=1;
	end
end