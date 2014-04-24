rate = 100;
Tmax = 10;
dt = 0.001;
T = linspace(0,Tmax,Tmax/dt);

mu = 0.05;
kappa = 5;
alpha = 0.04;
gamma = 0.5;
rho = -0.5;

cov = [1,rho;rho,1];

dW = sqrt(dt)*(1/sqrt(2))*cov*randn(2,length(T));
X = zeros(1,length(T));
v = zeros(1,length(T));
Y = zeros(1,length(T));
eta = 0.1*randn(1,length(T));

% generate v
v(1) = 0;
for i = 2:length(T)
   v(i) =  v(i-1) + kappa*(alpha - v(i-1))*dt + sqrt(v(i-1))*gamma*dW(1,i);
end

% generate X
X(1) = 0;
for i = 2:length(T)
    X(i) = X(i-1) + (mu - 0.5*v(i))*dt + sqrt(v(i))*dW(2,i);
end

% generate Y
for i = 1:length(T)
   Y(i) = X(i) + eta(i);
end

qv = 0;
for i = 1:rate:length(T)-rate
    qv = qv+(Y(i+rate)-Y(i))^2;
end

qv = qv/(2*Tmax/dt);
var(X)
var(Y)
qv
sigX = (0.5*dt/Tmax)*sum(diff(X).^2)
sigY = (0.5*dt/Tmax)*sum(diff(Y).^2)
% mean(v)
% 
plot(T,Y, 'Color', 'red')
hold on
plot(T,v, 'Color', 'black')
plot(T,X, 'Color', 'blue')
hold off
