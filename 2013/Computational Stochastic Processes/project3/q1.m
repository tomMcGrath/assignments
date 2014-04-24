clear all
clc

Tmax = 10000;
dt = 0.1;
dim = 10;
T = linspace(0,Tmax,Tmax/dt);

dW = randn(dim,length(T));
C = unifrnd(0,1,dim,dim);
C = C*C';
C = C./(max(max(C))+0.00000001);
X = zeros(dim, length(T));
Z = zeros(dim,dim);

%for i = 1:length(T)
%X(:,i) = mvnrnd(zeros(dim,1),C);
%end
Y = inv(C);

for k = 2:length(T)
    for i = 1:dim
        X(i,k) = dW(i,k)/sqrt(C(i,i));
        for j = 1:i-1
            X(i,k) = X(i,k) - (1/C(i,i))*X(j,k)*C(i,j);
        end
        
        for j = i+1:dim
            X(i,k) = X(i,k) - (1/C(i,i))*X(j,k-1)*C(i,j);
        end
    end
    k
end

for i = 1:length(T)
    Z = Z + (X(:,i)*transpose(X(:,i)));
end

Z = Z./length(T);
Z
inv(C)