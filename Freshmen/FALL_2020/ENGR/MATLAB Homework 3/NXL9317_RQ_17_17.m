%{

Name: Nghia Lam 
ID: 1001699317

Chapter 17 Question 17 Part A

D = Diameter(D)[ft]
P = Power(P)[hp]

%}
clc 
clear

%values
D = [.5 .75 1 1.5 2 2.25 2.5 2.75];
P = [.004 .04 .13 .65 3 8 18 22];

%Graph
plot(D,P,'ko','MarkerFaceColor','k');
title('Power Used VS Diamiter of Impeller')
xlabel('Diamiter(d)[ft]')
ylabel('Power(P)[hp]')
grid on
axis([0 3, 0 25]);

