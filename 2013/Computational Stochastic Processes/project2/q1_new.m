clear all
clc
%randn('state',100)
numRuns = 100;
Tmax = 1000; dt = 0.01;
T = linspace(0,Tmax,Tmax/dt);
dWX = sqrt(dt)*randn(numRuns,length(T)); % vectorise for speed
dWY = sqrt(dt)*randn(numRuns,length(T));
X = zeros(numRuns,length(T)); % initialise for speed
Y = zeros(numRuns, length(T));
x0 = 1.0;
y0 = 1.0;
kappa = 1;
omega = 1;

for i = 1:numRuns
    X_j = x0;
    Y_j = y0;
    for j = 1:length(T)
       incY =  sqrt(2.0*kappa)*dWY(i,j);
       Y_j = Y_j + sin(X_j)*sin(omega*(j*dt)) + incY;
       Y(i,j) = Y_j;
       incX = sqrt(2.0*kappa)*dWX(i,j);
       X_j = X_j + incX;
       X(i,j) = X_j;
    end
end

% hold on
% for i = 1:numRuns
%    plot(X(i,:), 'Color', 'green')
%    plot(Y(i,:))
% end
% hold off

plot(T,0.5*var(Y)./T)