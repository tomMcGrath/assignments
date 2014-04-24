clear all
clc
numRuns = 1;
rate = linspace(1,500,500);
results = zeros(numRuns,length(rate));
results2 = zeros(numRuns,length(rate));

for i = 1:length(rate)
    for j = 1:numRuns
        results(j,i) = MQfn(i);
    end
end

% for i = 1:length(rate)
%     for j = 1:numRuns
%         results2(j,i) = MQfn2(i);
%     end
% end

br = MQfn(1);

plot(rate,results)
% hold on
% plot(rate, var(results2), 'Color', 'black')
% hold off