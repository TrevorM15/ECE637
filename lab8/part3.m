%%
img = imread('house.tif');
img = double(img);
%%
b=img;
T=127;
b(b<=T)=0;
b(b>T)=255;
h1=figure; image(uint8(b)); colormap(gray(256)); truesize(h1, size(b));
RMSE = sqrt(1/(size(b,1)*size(b,2))*sum(sum(img-b)).^2);
fid = fidelity(img,b);

