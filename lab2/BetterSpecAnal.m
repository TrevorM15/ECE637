function BetterSpecAnal(img)

X = double(img)/255;
N = 64;
w = hamming(N)*hamming(N)';
z = zeros(N,N,25);
Z=z;
Zabs=z;
centx = ceil(size(img,1)/2);
centy = ceil(size(img,2)/2);
ind = ceil(N/2);
k=1;
for i = -2:2
    for j = -2:2
        z(:,:,k) = X(centx+i*N-ind:centx+i*N+ind-1,centy+j*N-ind:centy+j*N+ind-1);
        k = k+1;
    end
end


% Compute the power spectrum for the NxN region
for k = 1:25
    z(:,:,k) = z(:,:,k).*w;
    Z(:,:,k) = (1/N^2)*abs(fft2(z(:,:,k))).^2;
    % Use fftshift to move the zero frequencies to the center of the plot
    Z(:,:,k) = fftshift(Z(:,:,k));
    % Compute the logarithm of the Power Spectrum.
    Zabs(:,:,k) = log(Z(:,:,k));
end

Zavg = mean(Zabs,3);
% Plot the result using a 3-D mesh plot and label the x and y axises properly. 

x = 2*pi*((0:(N-1)) - N/2)/N;
y = 2*pi*((0:(N-1)) - N/2)/N;
figure 
mesh(x,y,Zavg)
xlabel('\mu axis')
ylabel('\nu axis')
end