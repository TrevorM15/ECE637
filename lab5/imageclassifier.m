function class = imageclassifier(img, params,A,u, varargin)
Xz=img-u;
Y=A'*Xz;
c=zeros(26,1);
if nargin == 4
    for k=1:26
        uk=params(k).M;
        R=params(k).R;
        c(k)=(Y-uk)'*inv(R)*(Y-uk)+log(det(R));
    end
    class=find(c<=min(c));
elseif nargin==5
    for k=1:26
        uk=params(k).M;
        switch varargin{1}
            case 'lazy'
                R=eye(10);
            case 'diag'
                R=params(k).R;
            R=diag(diag(R)); %B_k=diagonal of cov
            case 'avg'
                for j=1:26
                    R=1/26*sum(params(j).R,3); %B_k = average cov
                end
            case 'diagavg'
                for j=1:26
                    R=1/26*sum(params(j).R,3); %B_k = average cov
                end
                R=diag(diag(R)); %B_k = diagonal of avg cov
            otherwise
                R=params(k).R;
        end
        c(k)=(Y-uk)'*inv(R)*(Y-uk)+log(det(R));
        class=find(c<=min(c));
    end
end
