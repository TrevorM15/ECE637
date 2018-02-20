read_data;
u = 1/size(X,1).*sum(X,1);
Xz=X-u;
Z=1/sqrt(size(X,2)-1)*Xz;
[U,S,V]=svd(Z,0);
eigimg=U(:,1:12);
eigimgp=reshape(eigimg,64,64,12);
figure;
for i=1:12
subplot(4,3,i);
imagesc(eigimgp(:,:,i));colormap(gray(256));
end
%%
Y = U'*Xz;
figure;plot(Y(1:10,1:4));legend('a','b','c','d');
title('Projection Coefficients vs. Eigenvector Number');xlabel('Eigenvector Number')
m = [1,5,10,15,20,30];
figure;imagesc(reshape(X(:,1),64,64,1));colormap(gray(256));title('Original Image')
figure;
for i=1:length(m)
    subplot(3,2,i)
    imagesc(reshape(U(:,1:m(i))*Y(1:m(i),1),64,64,1));colormap(gray(256))
    title(['Resynthesized, m = ' num2str(m(i))])
end
