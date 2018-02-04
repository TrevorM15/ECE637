g=127:255;
a = zeros(2);
b = 255*ones(2);
c = [b a; a b];
d = repmat(c, 4, 64);
d=repmat(d,1,1,length(g));
e=ones(16,256,length(g));
for i = 1:length(g)
   e(:,:,i) = g(i).*e(:,:,i); 
end
f=[d;e];
h=repmat(f, 8,1);
%%
for i=1:length(g)
fig=figure(1); 
image(h(:,:,i)); 
truesize(fig)
colormap(gray(256))
title(['\fontsize{20}Gamma:',num2str(g(i))]);
pause(1)

end
% gamma is around 163-170 on my right monitor, I'd say 165 is the best
%% 
figure(1)
image(h(:,:,38));
title('Gamma of 165')
%% Gamma Correction
lin = imread('linear.tif');

fig2=figure(2); image(lin);title('linear.tif uncorrected'); colormap(gray(256));
truesize(fig2)

lin = double(lin);
linc=255*(lin/255).^(1/1.6);
linc=uint8(linc);
fig3=figure(3);image(linc); truesize(fig3)
title('linear.tif gamma corrected \gamma = 1.6');colormap(gray(256));

lin15 = imread('gamma15.tif');
lin15 = im2double(lin15);
lin15c=lin15.^(1.5/1.6);
lin15c=uint8(255*lin15c);
fig4=figure(4);image(lin15c); truesize(fig4)
title('linear.tif gamma corrected from \gamma = 1.5 to \gamma = 1.6');colormap(gray(256));


