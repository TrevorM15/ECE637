Y = imread('img14g.tif');
Y = im2double(Y);
X=imread('img14sp.tif'); %change this to filter different images
X=im2double(X);
Z = zeros(floor(size(Y,1)/20)*floor(size(Y,2)/20), 7, 7);
y=zeros(25,38);
k = 1;
l=1;
m=1;
for i = floor(linspace(4, 509,floor(size(Y,1)/20)))
    for j = floor(linspace(4,765,floor(size(Y,2)/20)))
    Z(k,:,:) = X(i-3:i+3, j-3:j+3);
    y(l,m)=Y(i,j);
    k=k+1;
    m=m+1;
    end
    m=1;
    l=l+1;
end
Z = reshape(Z, 950, 49);
y = reshape(permute(y, [2 1]), 950,1);
Rzz=Z'*Z./950;
rzy=Z'*y./950;
theta=Rzz\rzy;
theta= reshape(theta, 7,7);
Xhat=imfilter(X,theta);
Xhat=255*Xhat;
Xhat(Xhat<0)=0;
Xhat(Xhat>255)=255;
figure; image(uint8(Xhat)); colormap(gray(256))
