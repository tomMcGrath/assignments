Tmax = 100;
dt = 0.1;
mu = 0.5;
numRuns = 10;
T = linspace(0,Tmax,Tmax/dt);
dW = randn(numRuns,length(T));
X = zeros(numRuns,length(T));
lambda = -1.0;
theta = 0.5;

% EM scheme
% for i = 1:numRuns
%    X_j = 1.1;
%    X(i,1) = X_j;
%    for j = 2:length(T)
%       X_j = X_j - lambda*X_j*(1-X_j)*dt - mu*X_j*(1-X_j)*sqrt(dt)*dW(i,j);
%       X(i,j) = X_j;
%    end
% end

% % Milstein scheme
% for i = 1:numRuns
%    X_j = 1.1;
%    X(i,1) = X_j;
%    for j = 2:length(T)
%       X_j = X_j - lambda*X_j*(1-X_j)*dt - mu*X_j*(1-X_j)*sqrt(dt)*dW(i,j) - 0.5*(mu*mu*X_j*(1-X_j) - 2*mu*mu*X_j*X_j*(1-X_j));
%       X(i,j) = X_j;
%    end
% end

% semi-implicit Milstein scheme
for i = 1:numRuns
   X_j = 1.1;
   X(i,1) = X_j;
   for j = 2:length(T)
       % use anonymous function to define newton-raphson root quickly
       milstein = @(x) x*(1+theta*lambda*dt*(1-x)) - (X_j - lambda*X_j*(1-X_j)*dt - mu*X_j*(1-X_j)*sqrt(dt)*dW(i,j) - 0.5*(mu*mu*X_j*(1-X_j) - 2*mu*mu*X_j*X_j*(1-X_j)));
       x = fzero(milstein, X_j);
       X_j = x;
       X(i,j) = X_j;
   end
end

err = (X-1);
err = err.^2;
mErr = mean(err);
plot(mErr, 'Color', 'black')

% hold on
% for i = 1:numRuns
%    plot(X(i,:)) 
% end
% hold off