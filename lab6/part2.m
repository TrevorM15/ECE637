<<<<<<< HEAD
%% part 2
figure; plot([x' y' z']); legend('x_0(\lambda)', 'y_0(\lambda)', 'z_0(\lambda)');xlabel('\lambda'); title('XYZ Color Matching Functions')
Ainv=[0.2430  0.8560 -0.0440;
     -0.3910  1.165   0.0870;
      0.0100 -0.0080  0.5630];
LMS=Ainv*[x; y; z];
l0=LMS(1,:);
m0=LMS(2,:);
s0=LMS(3,:);
figure; plot(l0' , 'r'); hold on; plot(m0', 'g'); plot(s0', 'b');title(' LMS Color Matching Functions')
legend('l_0(\lambda)', 'm_0(\lambda)', 's_0(\lambda)');xlabel('\lambda')
figure; plot([illum1' illum2']); title('D65 and Fluorescent Illuminants'); xlabel('\lambda'); legend('D_{65}', 'Fluorescent')
%% part 3
x0= @(lambda)x(lambda);
y0=@(lambda)y(lambda);
z0=@(lambda)z(lambda);
xchrom=@(lambda) x0(lambda)./(x0(lambda)+y0(lambda)+z0(lambda));
ychrom=@(lambda) y0(lambda)./(x0(lambda)+y0(lambda)+z0(lambda));
lambda = 1:31; 
chrom=[xchrom(lambda(:)); ychrom(lambda(:))];

D65wp=[0.3127; 0.3290; 0.3583];
xwp=D65wp(1);
ywp=D65wp(2);
zwp=D65wp(3);

Rcie=[0.73467, 0.26533, 0.0];
Gcie= [0.27376, 0.71741, 0.00883];
Bcie=[0.16658, 0.00886, 0.82456];
RG=[Rcie(1) Gcie(1);Rcie(2) Gcie(2) ];
RB=[Rcie(1) Bcie(1);Rcie(2) Bcie(2) ];
BG=[Bcie(1) Gcie(1);Bcie(2) Gcie(2) ];

h=figure;plot(chrom(1,:), chrom(2,:), 'k');xlabel('\lambda');title('Chromaticity');hold on; 
plot(Rcie(1), Rcie(2), 'r*'); text(Rcie(1), Rcie(2), 'Red');
plot(Gcie(1), Gcie(2), 'g*');text(Gcie(1)+0.01, Gcie(2), 'Green');
plot(Bcie(1), Bcie(2), 'b*');text(Bcie(1)+0.01, Bcie(2)+0.01, 'Blue');
h1=plot(RG(1,:), RG(2, :), 'r');plot(RB(1,:), RB(2, :), 'r');plot(BG(1,:), BG(2, :), 'r')

R709=[0.640, 0.330, 0.030];
G709= [0.300, 0.600, 0.100];
B709=[0.150, 0.060, 0.790];
RG=[R709(1) G709(1);R709(2) G709(2) ];
RB=[R709(1) B709(1);R709(2) B709(2) ];
BG=[B709(1) G709(1);B709(2) G709(2) ];



plot(R709(1), R709(2), 'r*'); text(R709(1), R709(2), 'Red');
plot(G709(1), G709(2), 'g*');text(G709(1)+0.01, G709(2), 'Green');
plot(B709(1), B709(2), 'b*');text(B709(1)+0.01, B709(2)+0.01, 'Blue');
h2=plot(RG(1,:), RG(2, :), 'b');plot(RB(1,:), RB(2, :), 'b');plot(BG(1,:), BG(2, :), 'b');
plot(xwp, ywp, 'k*');text(xwp, ywp-0.015, 'White Point');plot(0.3333, 0.3333, 'k*');
text(0.342, 0.34,'Equal Energy');orient(h, 'tall');legend([h1 h2], 'CIE 1931', 'Rec 709'); hold off;
print('fig4', '-dpng')

%% part 4
I = zeros(size(R));
for i = 1:31
I(:,:,i) = R(:,:,i).*illum1(1,i); %change illum to 1 or 2 for d65 or fluorescent
end
XYZ=zeros(size(R,1), size(R,2), 3);
for i = 1:31
    XYZ(:,:,1)=XYZ(:,:,1)+x(1,i).*I(:,:,i);
    XYZ(:,:,2)=XYZ(:,:,2)+y(1,i).*I(:,:,i);
    XYZ(:,:,3)=XYZ(:,:,3)+z(1,i).*I(:,:,i);
end

m=[R709' G709' B709'];
k = m\[xwp/ywp; 1; zwp/ywp];
M = m*diag(k);

rgb=zeros(size(XYZ));

for i = 1:size(XYZ, 1)
    for j = 1:size(XYZ,2)
        rgb(i,j,:)=M\permute(XYZ(i,j,:), [3 2 1]);
    end
end
rgb(rgb<0)=0;
rgb(rgb>1)=1;
RGB=uint8(255*(rgb).^(1/2.2));
figure; image(RGB); title('D_{65} Source')
imwrite(RGB, 'fig5.png')
%% part 5
[xm,ym]= meshgrid(0:0.005:1, 0:0.005:1);
zm=1-xm-ym;
% zm(zm<0)=0;
rgb=zeros(201,201,3);
for i = 1:201
    for j = 1:201
        rgb(i,j,:)=m\[xm(i,j) ym(i,j) zm(i,j)]';
    end
end

for i = 1:201
    for j = 1:201
        if (rgb(i,j, 1)<0 || rgb(i,j, 2)<0 || rgb(i,j, 3)<0)
            rgb(i,j,1)=1;
            rgb(i,j,2)=1;
            rgb(i,j,3)=1;
        end
    end
end
RGB=(rgb).^(1/2.2);
%%
figure; image(0:.005:1,0:.005:1,RGB);hold on; plot(chrom(1,:), chrom(2,:), 'k'); 
axis('xy'); xlabel('\lambda');title(' Monitor Chromaticity Diagram');
plot(R709(1), R709(2), 'r*'); text(R709(1), R709(2), 'Red');
plot(G709(1), G709(2), 'g*');text(G709(1)+0.01, G709(2), 'Green');
plot(B709(1), B709(2), 'b*');text(B709(1)+0.01, B709(2)+0.01, 'Blue');
plot(RG(1,:), RG(2, :), 'k');plot(RB(1,:), RB(2, :), 'k');plot(BG(1,:), BG(2, :), 'k');
plot(xwp, ywp, 'k*');text(xwp-0.15, ywp-0.015, 'White Point');plot(0.3333, 0.3333, 'k*');
text(0.342, 0.34,'Equal Energy');hold off;









=======
%% part 2
figure; plot([x' y' z']); legend('x_0(\lambda)', 'y_0(\lambda)', 'z_0(\lambda)');xlabel('\lambda'); title('XYZ Color Matching Functions')
Ainv=[0.2430  0.8560 -0.0440;
     -0.3910  1.165   0.0870;
      0.0100 -0.0080  0.5630];
LMS=Ainv*[x; y; z];
l0=LMS(1,:);
m0=LMS(2,:);
s0=LMS(3,:);
figure; plot(l0' , 'r'); hold on; plot(m0', 'g'); plot(s0', 'b');title(' LMS Color Matching Functions')
legend('l_0(\lambda)', 'm_0(\lambda)', 's_0(\lambda)');xlabel('\lambda')
figure; plot([illum1' illum2']); title('D65 and Fluorescent Illuminants'); xlabel('\lambda'); legend('D_{65}', 'Fluorescent')
%% part 3
x0= @(lambda)x(lambda);
y0=@(lambda)y(lambda);
z0=@(lambda)z(lambda);
xchrom=@(lambda) x0(lambda)./(x0(lambda)+y0(lambda)+z0(lambda));
ychrom=@(lambda) y0(lambda)./(x0(lambda)+y0(lambda)+z0(lambda));
lambda = 1:31; 
chrom=[xchrom(lambda(:)); ychrom(lambda(:))];

D65wp=[0.3127; 0.3290; 0.3583];
xwp=D65wp(1);
ywp=D65wp(2);
zwp=D65wp(3);

Rcie=[0.73467, 0.26533, 0.0];
Gcie= [0.27376, 0.71741, 0.00883];
Bcie=[0.16658, 0.00886, 0.82456];
RG=[Rcie(1) Gcie(1);Rcie(2) Gcie(2) ];
RB=[Rcie(1) Bcie(1);Rcie(2) Bcie(2) ];
BG=[Bcie(1) Gcie(1);Bcie(2) Gcie(2) ];

figure;plot(chrom(1,:), chrom(2,:));xlabel('\lambda');title('Chromaticity');hold on; 
plot(Rcie(1), Rcie(2), 'r*'); text(Rcie(1), Rcie(2), 'Red');
plot(Gcie(1), Gcie(2), 'g*');text(Gcie(1)+0.01, Gcie(2), 'Green');
plot(Bcie(1), Bcie(2), 'b*');text(Bcie(1)+0.01, Bcie(2)+0.01, 'Blue');
plot(RG(1,:), RG(2, :), 'k');plot(RB(1,:), RB(2, :), 'k');plot(BG(1,:), BG(2, :), 'k');hold off;

R709=[0.640, 0.330, 0.030];
G709= [0.300, 0.600, 0.100];
B709=[0.150, 0.060, 0.790];
RG=[R709(1) G709(1);R709(2) G709(2) ];
RB=[R709(1) B709(1);R709(2) B709(2) ];
BG=[B709(1) G709(1);B709(2) G709(2) ];

figure;plot(chrom(1,:), chrom(2,:));xlabel('\lambda');title('Chromaticity');hold on; 
plot(R709(1), R709(2), 'r*'); text(R709(1), R709(2), 'Red');
plot(G709(1), G709(2), 'g*');text(G709(1)+0.01, G709(2), 'Green');
plot(B709(1), B709(2), 'b*');text(B709(1)+0.01, B709(2)+0.01, 'Blue');
plot(RG(1,:), RG(2, :), 'k');plot(RB(1,:), RB(2, :), 'k');plot(BG(1,:), BG(2, :), 'k');
plot(xwp, ywp, 'k*');text(xwp-0.12, ywp-0.015, 'White Point');plot(0.3333, 0.3333, 'k*');
text(0.342, 0.34,'Equal Energy');hold off;

%% part 4
I = zeros(size(R));
for i = 1:31
I(:,:,i) = R(:,:,i).*illum1(1,i);
end
XYZ=zeros(size(R,1), size(R,2), 3);
for i = 1:31
    XYZ(:,:,1)=XYZ(:,:,1)+x(1,i).*I(:,:,i);
    XYZ(:,:,2)=XYZ(:,:,2)+y(1,i).*I(:,:,i);
    XYZ(:,:,3)=XYZ(:,:,3)+z(1,i).*I(:,:,i);
end

m=[R709' G709' B709'];
k = m\[xwp/ywp; 1; zwp/ywp];
M = m*diag(k);

rgb=zeros(size(XYZ));

for i = 1:size(XYZ, 1)
    for j = 1:size(XYZ,2)
        rgb(i,j,:)=M\permute(XYZ(i,j,:), [3 2 1]);
    end
end
rgb(rgb<0)=0;
rgb(rgb>1)=1;
RGB=uint8(255*(rgb).^(1/2.2));
figure; image(RGB);

%% part 5
[xm,ym]= meshgrid(0:0.005:1, 0:0.005:1);
zm=1-xm-ym;
% zm(zm<0)=0;
rgb=zeros(201,201,3);
for i = 1:201
    for j = 1:201
        rgb(i,j,:)=m\[xm(i,j) ym(i,j) zm(i,j)]';
    end
end

for i = 1:201
    for j = 1:201
        if (rgb(i,j, 1)<0 || rgb(i,j, 2)<0 || rgb(i,j, 3)<0)
            rgb(i,j,1)=1;
            rgb(i,j,2)=1;
            rgb(i,j,3)=1;
        end
    end
end
RGB=(rgb).^(1/2.2);
figure; image(0:.005:1,0:.005:1,RGB); axis('xy'); hold on; title(' Monitor Chromaticity Diagram')
plot(R709(1), R709(2), 'r*'); text(R709(1), R709(2), 'Red');
plot(G709(1), G709(2), 'g*');text(G709(1)+0.01, G709(2), 'Green');
plot(B709(1), B709(2), 'b*');text(B709(1)+0.01, B709(2)+0.01, 'Blue');
plot(RG(1,:), RG(2, :), 'k');plot(RB(1,:), RB(2, :), 'k');plot(BG(1,:), BG(2, :), 'k');
plot(xwp, ywp, 'k*');text(xwp-0.15, ywp-0.015, 'White Point');plot(0.3333, 0.3333, 'k*');
text(0.342, 0.34,'Equal Energy');hold off;









>>>>>>> 0bd6a59720dbc96d0d668be961781754df4a84d7
