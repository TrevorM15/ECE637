%%
img = imread('house.tif');
img = double(img);
%%
T= 127;
imgl = 255*(img./255).^(2.2);
f = padarray(imgl, [0 1], 'both');
f = padarray(f, [1 0], 'post');
b=zeros(size(imgl));
for i = 1:size(b,1)
    for j = 1:size(b,2)
        if f(i,j+1) >T
            b(i,j) = 255;
        else
            b(i,j) = 0;
        end
        e= f(i,j+1)-b(i,j);
        f(i, j+2) = 7/16*e+f(i, j+2);
        f(i+1, j) = 3/16*e+f(i+1,j);
        f(i+1, j+1) = 5/16*e+f(i+1,j+1);
        f(i+1,j+2) = 1/16*e+f(i+1,j+2);
    end
end
RMSE = sqrt(1/(size(b,1)*size(b,2))*sum(sum(img-b)).^2);
fid = fidelity(img,b);
h1 = figure; image(b); truesize(h1, size(b));colormap(gray(256));
imwrite(b, 'C:\Users\sleep\Documents\MATLAB\ECE637\lab8\figures\errordif.png');