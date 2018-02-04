function z = equalize(x)
xc = histcounts(x,256);
i=1:256;
m=1:size(x,1);
n=1:size(x,2);
F(i) = cumsum(xc(i))/sum(xc);
y(m,n)=F(x(m,n));
z(m,n) = 255*(y(m,n)-min(min(y)))/(max(max(y))-min(min(y)));

end