clear all
clc
results = zeros(10,1);
T = linspace(1,10,10);
for i = 1:length(T)
   results(i) = q2fn(T(i),0.0001,0.01);
   i
end

plot(epsilon,results)