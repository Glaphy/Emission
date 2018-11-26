function v=matreform(A)

dim=size(A);
rows=dim(1);
cols=dim(2);
v=[];

for i=1:rows
	for j=1:cols
		v=[v; A(i,j)];
	end
end