function A=vecreform(v, n)

l=length(v);
A=zeros(n,n);
row=1;
for i=1:l
	col=1;
	if(mod(i,n)~=0)
		col=mod(i,n);
		A(row,col)=v(i);
	else
		A(row,n)=v(i);
		row=row+1;
	end
end