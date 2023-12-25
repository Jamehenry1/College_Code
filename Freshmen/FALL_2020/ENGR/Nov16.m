clc
clear
close all
t = [ 0.1, 0.4, 3.6, 4.9, 8.0 ]; %x-axis time (t)[min]
P = [13800, 11100, 8900, 7300, 4000]; %y-axis Pressure(P)[Pa]

figure('color', 'w')
plot(t,P,'red s', 'MarkerFaceColor', 'r','MarkerSize', 15)
grid on

%-----2nd part: Theoretical -----
%polyfit()-> 1st order polynomial: y=mx+b; N = 1 for all problems
c = polyfit(t,P,1);

m = c(1);
b = c(2);  %y = -1.1008e+03 x + 1.2763e+4
%x_pf = [1:20];  goes beyond the original data 
x_pf = [.1:.01:8];
y_pf = m *x_pf +b;

hold on
plot(x_pf,y_pf,'--g','LineWidth',3)

% one more step: put trendline on graph, P = -1.1008e+03 x + 1.2763e+4
TE = sprintf('P = %.02ft + %0.2f', m,b);

text(1,4000,TE,'EdgeColor','b')
