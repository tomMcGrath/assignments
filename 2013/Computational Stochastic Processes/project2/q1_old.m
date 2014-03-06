%randn('state',100)
numRuns = 500;
T = 100; N=2^8; dt = 1/N;
dW1 = sqrt(dt)*randn(numRuns,N);
dW2 = sqrt(dt)*randn(numRuns,N);
R = 4; Dt = R*dt; L = N/R;
X = zeros(numRuns,L);
Y = zeros(numRuns,L);
x0 = 1.0;
y0 = 1.0;
kappa = 10;
omega = 1;
v_X = zeros(numRuns, L);
v_Y = zeros(numRuns, L);

X_j = x0;
Y_j = y0;
for i = 1:numRuns
    for j=1:L
        inc1 = sum(dW1(i,R*(j-1)+1:R*j));
        inc2 = sum(dW2(i,R*(j-1)+1:R*j));
        Y_j = Y_j + Dt*sin(X_j)*sin(omega*R*(j-1)) + sqrt(2*kappa)*inc1;
        Y(i,j) = Y_j;
        X_j = X_j + sqrt(2*kappa)*inc2;
        X(i,j) = X_j;
    end
end
hold on
for i = 1:numRuns
   plot(X(i,:), 'Color', 'green')
   plot(Y(i,:))
end
hold off

v_X = var(X,0,1);
v_Y = var(Y,0,1);