function [ qv ] = MQfn2( rate )
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

grids = zeros(1,rate);

for i = 1:rate
   for j = i:rate:(length(T)-rate)
      grids(i) = grids(i) + (Y(j+rate)-Y(j))^2;
   end
end

qv = mean(grids);
qv = rate*qv/(2*Tmax/dt);

end

