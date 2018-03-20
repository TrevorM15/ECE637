N=512;
x = rand(N,N)-0.5;
x_scaled = 225*(x+0.5);
h=figure; image(x_scaled);
map=gray(256);
colormap(map);
colorbar;
truesize(h, [512, 512])
title('x')
xPad = padarray(x,[1 1],'pre');
y = zeros(512);
for i = 1: size(y,1)
    for j = 1:size(y,2)
        if i==1 && j ==1
            y(i,j) = 3*xPad(i,j);
        elseif i ==1
            y(i,j) = 3*xPad(i,j)+0.99*y(i,j-1);
        elseif j ==1
            y(i,j) = 3*xPad(i,j)+0.99*y(i-1,j);
        else
        y(i,j) = 3*xPad(i,j)+0.99*y(i-1,j)+0.99*y(i,j-1)...
            -0.9801*y(i-1,j-1);
        end
    end
end
% y_scaled = 255*(y+0.5);
% y_scaled(y_scaled<0)=0;
% y_scaled(y_scaled>255)=255;
% y_scaled = uint8(y_scaled);
h=figure; imagesc(y+127);
colormap(map);
truesize(h, [512, 512])
colorbar;
title('y')

H = @(u,v) 3./(1-0.99*exp(-1j*u)-0.99*exp(-1j*v)...
    +0.9801*exp(-1j*(u+v)));
U = linspace(-pi,pi,512);
[u,v] = meshgrid(U,U);
figure; mesh(U,U,log(abs(H(u,v)).^2));
title(' S_{y}(e^{ju},e^{jv})=|H(e^{ju},e^{jv})|^2 ')
xlabel('\mu axis')
ylabel('\nu axis')

BetterSpecAnal(y)
title('S_{y}(e^{ju},e^{jv}) Estimate')
