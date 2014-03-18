clear all
clc

L = 10;
kappa = 1;
alpha = linspace(0.01,L,100);
results = zeros(1,length(kappa));

for i = 1:length(alpha)
    results(i) = q1bfn(kappa,alpha(i));
end

plot(alpha, results)
set(gca,'XTick',0.01:1:10)