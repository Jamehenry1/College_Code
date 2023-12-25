clear
clc
R = 0.08207;
V = 10;
N2mv = 28;
T_i = 270;
T_f = 350;
P_i = 2.54;
T = [T_i:0.5:T_f];
n = P_i *V/(R*T_i);
P = n * R * T/V;
plot(T,P);
axis([260,360,2.3,3.2]);
grid
