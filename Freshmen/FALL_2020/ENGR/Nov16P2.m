
clear 
clc 
close all

V= [ 0.7, 1.4, 3.6, 4.9, 8.0 ]; % volume (V)[m^3] y axis
SG= [ 0.0081, 0.0039, 0.0014, 0.00099, 0.00052 ]; %specific gravity(SG)[-] x-axis
%Plot the data, what type of model does it look like to you?
%Power, y = b x^m;

plot(SG,V,'red s', 'MarkerFaceColor','r','MarkerSize',10)

c = polyfit(log(SG),log(V),1);
m = c(1);
b = exp(c(2));
grid on
Rpf = [.0005:.001: .01];
Vpf = b*Rpf.^m;

hold on

plot(Rpf,Vpf,'--b','LineWidth',3);


