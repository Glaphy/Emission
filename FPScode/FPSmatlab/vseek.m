function A=vseek(A,b)

L=length(b);

for i=1:L
	if b(i)~=0
		A(i,:)=0;
		A(i,i)=1;
	end
end