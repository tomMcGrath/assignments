function [ errT ] = q2fn( Tmax, dt, epsilon )
numRuns = 100;
theta = 1.0;
T = linspace(0,Tmax,Tmax/dt);
dW = randn(numRuns,length(T));
X = zeros(numRuns,length(T));
Y = zeros(numRuns,length(T));
Z = zeros(numRuns,length(T));

% use Milstein scheme on Y - equivalent to EM as sigma' = 0
for i = 1:numRuns
    Y_j = randn();
    Y(i,1) = Y_j;
    for j = 2:length(T)
        Y_j = Y_j - Y_j*(dt/epsilon)/epsilon + (sqrt(2)/epsilon)*sqrt(dt)*dW(i,j);
        %Y_j = Y_j - Y_j*(dt/(epsilon^2)) + (sqrt(2)/epsilon)*sqrt(dt)*dW(i,j);
        Y(i,j) = Y_j;
    end
end

% % use implicit EM scheme on Y
% for i = 1:numRuns
%     Y_j = randn();
%     Y(i,1) = Y_j;
%     for j = 2:length(T)
%         Y_j = (1/(1+((theta*dt)/(epsilon^2))))*(Y_j - (1-theta)*Y_j*dt/(epsilon^2) + (sqrt(2)/epsilon)*sqrt(dt)*dW(i,j));
%         Y(i,j) = Y_j;
%     end
% end

% % use stochastic theta with EM scheme to obtain y series first - probably a
% % mistake in here as it doesn't work for theta around 0 or 1
% for i = 1:numRuns
%     Y_j = randn();
%     Y(i,1) = Y_j;
%     for j = 2:length(T)
%         Y_j = (epsilon^2/(epsilon^2+theta))*Y_j + ((theta - 1)/(epsilon^2 + theta))*Y_j*dt + (sqrt(2)/(epsilon + (theta/epsilon)))*dW(i,j); % check this
%         Y(i,j) = Y_j;
%     end
% end

% now solve the equation in x using the y series
for i = 1:numRuns
    X_j = 1.0;
    X(i,1) = X_j;
    for j = 2:length(T)
        X_j = X_j + ((X_j*Y(i,j))/epsilon)*dt - ((X_j^3)*(Y(i,j)^2))*dt;
        X(i,j) = X_j;
    end
end

% using explicit Milstein for eq(2c)
for i = 1:numRuns
    Z_j = 1.0;
    Z(i,1) = 1.0;
    for j = 2:length(T)
        Z_j = Z_j + (Z_j - Z_j^3)*dt + sqrt(2)*Z_j*sqrt(dt)*dW(i,j) + Z_j*dt*(dW(i,j)*dW(i,j) - 1);
        Z(i,j) = Z_j;
    end
end

err = (Z - X);
err = err.^2;
errT = err(length(T))
%mErr = mean(err);
%errT = mErr(length(T));

hold on
for i = 1:numRuns
   %plot(Z(i,:), 'Color', 'green')
   %plot(Y(i,:), 'Color', 'blue')
   plot(X(i,:), 'Color', 'red')
   %plot(err(i,:))
end
% plot(mErr, 'Color', 'black')
% mErr(length(T))
% hold off
end

