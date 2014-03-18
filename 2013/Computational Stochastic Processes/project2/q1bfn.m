function [ D_T ] = q1bfn( kappa, alpha )

numRuns = 100;
Tmax = 1000; dt = 0.01;
T = linspace(0,Tmax,Tmax/dt);
dWX = sqrt(dt)*randn(numRuns,length(T)); % vectorise for speed
dWY = sqrt(dt)*randn(numRuns,length(T));
dWEta = sqrt(dt)*randn(numRuns,length(T));
X = zeros(numRuns,length(T)); % initialise for speed
Y = zeros(numRuns, length(T));
eta = zeros(numRuns, length(T));
x0 = 1.0;
y0 = 1.0;

% all schemes currently explicit method, could adapt eta and y to implicit
% EM or Milstein easily as they are linear
for i = 1:numRuns
    X_j = x0;
    X(i,1) = X_j;
    Y_j = y0;
    Y(i,1) = Y_j;
    eta_j = randn();
    eta(i,1) = eta_j;
    for j = 2:length(T)
       incY =  sqrt(2.0*kappa)*dWY(i,j);
       Y_j = Y_j + sin(X_j)*eta_j*dt + incY;
       Y(i,j) = Y_j;
       incX = sqrt(2.0*kappa)*dWX(i,j);
       X_j = X_j + incX;
       X(i,j) = X_j;
       incEta = sqrt(2.0*alpha)*dWEta(i,j);
       eta_j = eta_j - alpha*eta_j*dt + incEta;
       eta(i,j) = eta_j;
    end
end

D = var(X)./T;
D_T = D(length(T));

end

