results = zeros(100,1);
epsilon = 0.01;
for i = 1:10
   results(i) = q2fn(10,0.00001,epsilon);
   epsilon = epsilon + 0.001;
   i
end

plot(results(1:10))