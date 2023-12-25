clear
clc

figure('Color','w');
P = [12 23 37 47 59 79];
v = [2.5 2.95 3.3 3.55 3.7 3.9 ];
v2 = [3.5 4.95 6.3 7.55 8.7 9.9];
plot(P,v,'mp', 'MarkerFaceColor','m','MarkerSize',10);

axis([0 100,0 10])
grid on
