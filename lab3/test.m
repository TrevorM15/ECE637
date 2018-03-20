img = imread('img22gd2.tif');
img = double(img);
Y = zeros(size(img)); 
s = [67, 45];
T = 4;
stack = s;
%%
while ~isempty(stack)
    [Y, stack] = connectedSet(s,T,img,stack, Y);
    stack = stack(2:end,:);
    if ~isempty(stack)
        s = stack(1,:);
    end
%     subplot(1,2,1)
%     imagesc(img); colormap(gray);
%     drawnow;
%     subplot(1,2,2)
%     imagesc(Y); colormap(gray);
%     drawnow;
    
end
figure;
subplot(1,2,1)
imagesc(img); colormap(gray);
subplot(1,2,2)
imagesc(Y); colormap(gray);
%% functions
function c = connectedNeighbors(s,T, img)
    c =zeros(2);
    if (abs(img(s(1),s(2))-img(s(1)-1, s(2)))<=T) && (s(1)-1 >1)
        c(1,1)=1;
    end
    if (abs(img(s(1),s(2))-img(s(1)+1, s(2)))<=T) && (s(1)+1<size(img,1))
        c(2,1)=1;
    end
    if (abs(img(s(1),s(2))-img(s(1), s(2)-1))<=T) && (s(2)-1 >1)
        c(1,2)=1;
    end
    if (abs(img(s(1),s(2))-img(s(1), s(2)+1))<=T) && (s(2)+1<size(img,2))
        c(2,2)=1;
    end
end

function [Y, stack] = connectedSet(s,T,img, stack, Y)

    c = connectedNeighbors(s,T,img);
    
    if c(1,1) == 1 && Y(s(1)-1, s(2))==0
        Y(s(1)-1, s(2))=1;
        stack = [stack; s(1)-1, s(2)];
    end
    if c(2,1) == 1 && Y(s(1)+1, s(2))==0
        Y(s(1)+1, s(2))=1;
        stack = [stack; s(1)+1, s(2)];
    end
    if c(1,2) == 1 && Y(s(1), s(2)-1)==0
        Y(s(1), s(2)-1)=1;
        stack = [stack; s(1), s(2)-1];
    end
    if c(2,2) == 1 && Y(s(1), s(2)+1)==0
        Y(s(1), s(2)+1)=1;
        stack = [stack; s(1), s(2)+1];
    end
    
end

