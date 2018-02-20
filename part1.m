RX=[2 -1.2;-1.2 1];
W = eye(2)*randn(2,1000);
[E,lambda]=eig(RX);
Xt=lambda.^(1/2)*W;
X=E*Xt;
figure(1);
plot(W(1,:),W(2,:),'.');axis('equal');title('W')
figure(2)
plot(Xt(1,:),Xt(2,:),'.');axis('equal');title('\~ X', 'interpreter', 'latex')
figure(3)
plot(X(1,:),X(2,:),'.');axis('equal');title('X')
%%
u=1/1000*sum(X,1);
Z=X-u;
R=1/(1000-1).*Z*Z'; %pretty close to theoretical values
[E,lambda]=eig(R);
Xt=E'*X;
lambdai=diag(lambda(lambda~=0).^(-1/2));
W=lambdai*Xt;
uw=1/1000*sum(W,1);
RW=1/999*(W-uw)*(W-uw)';
figure(4);
plot(W(1,:),W(2,:),'.');axis('equal');title('W')
figure(5)
plot(Xt(1,:),Xt(2,:),'.');axis('equal');title('\~ X', 'interpreter', 'latex')
figure(6)
plot(X(1,:),X(2,:),'.');axis('equal');title('X')