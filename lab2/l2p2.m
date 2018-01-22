x = rand(512)-0.5;
x_scaled = 225*(x+0.5);
h=figure; image(x_scaled);
map=gray(256);
colormap(map);
colorbar;
truesize(h, [512, 512])
title('x')
xPad = padarray(x,[1 1],'pre');
y = zeros(512);
for i = 2: size(xPad,1)
    for j = 2:size(xPad,2)
        y(i-1,j-1) = 3*xPad(i,j)+0.99*(xPad(i-1,j)+xPad(i,j-1))-0.9801*xPad(i-1,j-1);
    end
end

h=figure; image(y+127);
colormap(map);
truesize(h, [512, 512])
colorbar;
title('y')

H = @(u,v) 3./(1-0.99*(exp(-1j*2*pi*u)+exp(-1j*2*pi*v))+0.9801*exp(-1j*2*pi*(u+v)));

[u,v] = meshgrid(1:512,1:512);

figure; mesh(abs(H(u,v)^2));

BetterSpecAnal(y)