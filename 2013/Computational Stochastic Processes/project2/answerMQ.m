mu = [0.5, 0.6, 0.7, 0.8, 0.9];
Tmax = 0.2;
dt = 0.01;
T = linspace(0,Tmax,Tmax/dt);
hold on
for i = 1:length(mu)
   plot(T,MQfn(Tmax,dt,mu(i)))
end
hold off
