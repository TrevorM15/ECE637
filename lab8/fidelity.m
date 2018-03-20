function fid = fidelity(f,b)
fl = 255*(f./255).^(2.2);
bl=255*(b./255).^(2.2);
var = 2;

h = @(i,j) exp(-(i.^2+j.^2)./(2*var));
[a,b]=meshgrid(-3:3,-3:3);
c=1/sum(sum(h(a,b)));
h = @(i,j) c*exp(-(i.^2+j.^2)./(2*var));
ft = padarray(fl, [3 3], 0, 'both');
bt= padarray(bl, [3 3], 0, 'both');
for i = 4:size(ft,1)-3
    for j = 4:size(ft,2)-3
        ind1=i-3:i+3;
        ind2=j-3:j+3;
        ft(i,j) = sum(sum(ft(ind1,ind2 ).*h(a,b)));
        bt(i,j) = sum(sum(bt(ind1, ind2).*h(a,b)));
    end
end
ft = ft(4:size(ft,1)-3, 4:size(ft,2)-3);
bt= bt(4:size(bt,1)-3, 4:size(bt,2)-3);
ft = 255*(ft./255).^(1/3);
bt = 255*(bt./255).^(1/3);
fid = sqrt(1/(size(bt,1)*size(bt,2))*sum(sum(ft-bt))^2 );
end