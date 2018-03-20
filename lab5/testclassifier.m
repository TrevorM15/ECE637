datachar='abcdefghijklmnopqrstuvwxyz';
comp=zeros(26,2);
[params,A,u]=trainclassifier();
for k = 1:26
    fname=sprintf('veranda/%s.tif',datachar(k));
    img=imread(fname);
    img = reshape(double(img),size(img,1)*size(img,2),1);
    classest=imageclassifier(img,params,A,u,'diagavg');
    comp(k,:)=[ datachar(k) datachar(classest)];
end
%%
cols={'Input','Mapped'};
comp=char(comp);
misclass=comp(comp(:,1)~=comp(:,2),:);
T=table(misclass(:,1),misclass(:,2),'VariableNames',cols);
