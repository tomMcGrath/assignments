clear all
clc

L = 10;
kappa = 0.1;
omega = linspace(0.01,L,100);
results = zeros(1,length(omega));

for i = 1:length(omega)
    results(i) = q1afn(kappa,omega(i));
end

plot(omega,results)
set(gca,'XTick',0:1:10)
