function [ output_args ] = MQfn( Tmax,dt,mu )
numRuns = 100;
T = linspace(0,Tmax,Tmax/dt);
dW = randn(numRuns,length(T));
X = zeros(numRuns,length(T));
Y = zeros(numRuns,length(T));
Z = zeros(numRuns,length(T));

for i = 1:numRuns
    X_j = 1.0;
    X(i,1) = 1.0;
    for j = 2:length(T)
        X_j = X_j + (X_j - X_j^3)*dt + sqrt(2)*X_j*sqrt(dt)*dW(i,j) + X_j*dt*(dW(i,j)*dW(i,j) - 1);
        X(i,j) = X_j;
    end
end

end

