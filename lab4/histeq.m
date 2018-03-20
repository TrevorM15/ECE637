race = imread('race.tif');
kids = imread('kids.tif');
% race=im2double(race);
% kids = im2double(kids);

figure(2)
histogram(race,255);
title('Histogram of race.tif');
ylabel('Pixel Count')

figure(1)
histogram(kids,255);

xlim([0 255]);
title('Histogram of kids.tif');
ylabel('Pixel Count')



%% CDFs of images
rc = histcounts(race,256);
kc = histcounts(kids,256);
i = 1:256;
Frace(i)=cumsum(rc(i))/sum(rc);
Fkids(i)=cumsum(kc(i))/sum(kc);
figure(3); plot(Frace); title('$$\hat{F(i)}_{race}$$','interpreter', 'latex')
figure(4); plot(Fkids);title('$$\hat{F(i)}_{kids}$$','interpreter','latex')

%% Histogram Equalization

yr=equalize(race);
figure(5);histogram(yr,256); title('Race.tiff Histogram Equalized');
figure(6);
image(yr);colormap(gray(256))
y=histcounts(yr,256);
F(i)=cumsum(y(i))/sum(y);
figure(7);plot(F);title('Race Equalized CDF')


yk=equalize(kids);
figure(8);histogram(yk,256); title('kids.tiff Histogram Equalized');
figure(9);
image(yk);colormap(gray(256))
y=histcounts(yk,256);
F(i)=cumsum(y(i))/sum(y);
figure(10);plot(F);title('Kids Equalized CDF')
%%  Contrast Stretching
y = stretch(kids,70,180);
figure(11);image(y);colormap(gray(256)); title('Kids Contrast Stretched')
figure(12); histogram(y); title('Kids Contrast Stretched Histogram');

%% Gamma
 






