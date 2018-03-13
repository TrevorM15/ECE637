%%
img = imread('house.tif');
img = double(img);
%%
imgl = 255*(img./255).^(2.2);
I2 = [1 2; 3 0];
I4 = [4*I2+1 4*I2+2; 4*I2+3 4*I2];
I8 = [4*I4+1 4*I4+2; 4*I4+3 4*I4];
I = {I2;I4;I8};
T = @(i,j, N) 255*(I{N}(i,j)+0.5)/4^N;
N=1;
b = zeros(size(imgl));
for i = 1:size(imgl,1)
    for j = 1:size(imgl,2)
        if imgl(i,j)>T(mod(i,2^N)+1, mod(j,2^N)+1,N)
            b(i,j)=255;
        else
            b(i,j)=0;
        end
    end
end
RMSE = sqrt(1/(size(b,1)*size(b,2))*sum(sum(img-b)).^2);
fid = fidelity(img,b);
h = figure; image(b); colormap(gray(256)); truesize(h, size(b))