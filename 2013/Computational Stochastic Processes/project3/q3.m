clear all
clc

Tmax = 1000;
dt = 0.1;
epsilon = 0.1;

T = linspace(0,Tmax,Tmax/dt);
X = zeros(1,length(T));
dW = randn(1,length(T));
m = zeros(1,length(T));
v = zeros(1,length(T));
k = zeros(1,length(T));
Y = linspace(-2,2,41);

X(1) = 0.0;
for i = 2:length(T)
    % part i
    %X(i) = X(i-1) - X(i-1)*dt + sqrt(dt)*dW(i);
    % part iii
    X(i) = X(i-1) + (X(i-1)-X(i-1)^3)*dt + sqrt(dt)*dW(i);
end

for j = 1:length(T)
    m(j) = mean(X(1:j));
    v(j) = moment(X(1:j),2);
    k(j) = moment(X(1:j),4);
    j
end

figure
subplot(2,1,1);
hold on
    plot(T,m)
    plot(T,v, 'Color', 'black')
    plot(T,k, 'Color', 'green')
hold off

subplot(2,1,2);
hist(X,Y)