clear all
clc

numRuns = 1000;
Tmax = pi; dt = 0.0001;
T = linspace(0,Tmax,Tmax/dt);
dWX = randn(numRuns,length(T)); % vectorise for speed
dWY = randn(numRuns,length(T));
X = zeros(numRuns,length(T)); % initialise for speed
Y = zeros(numRuns, length(T));
D = zeros(1,length(T));
x0 = 1;
y0 = 0;
kappa = 2;
omega = 1;

for i = 1:numRuns
    X_j = x0;
    X(i,1) = X_j;
    for j = 2:length(T)
        X_j = X_j + sqrt(dt)*sqrt(2*kappa)*dWX(i,j);
        X(i,j) = X_j;
    end
end

for i = 1:numRuns
    Y_j = y0;
    Y(i,1) = Y_j;
    for j = 2:length(T)
        Y_j = Y_j + sin(X(i,j))*sin(omega*T(j))*dt + sqrt(dt)*sqrt(2*kappa)*dWY(i,j);
        Y(i,j) = Y_j;
    end
end

% D = var(X)./(2*T);
% plot(T,D)

% hold on
% for i = 1:numRuns
%    plot(X(i,:), 'Color', 'green')
%    plot(Y(i,:))
% end
% hold off

hold on
plot(T, mean(Y))
%plot(T,var(Y),'Color','black')
%plot(T, mean(X), 'Color', 'green')
hold off