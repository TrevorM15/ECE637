function [params,A,u] = trainclassifier()
read_data
empty_cell=cell(26,2);
params=cell2struct(empty_cell,{'M','R'},2);

u = 1/size(X,2).*sum(X,2);
Xz=X-u;
Z=1/sqrt(size(X,2)-1)*Xz;
[U,~,~]=svd(Z,0);
A=U(:,1:10);
Y=A'*Xz;
ck=size(Y,2)/26;
b=zeros(10,10,12);
for k = 1:26
    d=Y(:,k:26:286+k); %grab all of the vectors of class k
   params(k).M=1/ck*sum(d,2); %average image vector from k images
   for i=1:size(d,2)
   a=d(:,i)-params(k).M;
   b(:,:,i)=a*a';
   end
   params(k).R=1/(ck-1).*sum(b,3);
end
end
