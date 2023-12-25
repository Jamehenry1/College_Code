%{

Name: Nghia Lam 
ID: 1001699317

Chapter 16 Question 11
Determine how long, in units of seconds,
it will take a motor to raise a load into the air.
What is Time[s]?

eff = .6
Pin = 100[W]
M = 100[kg]
H = 5[m]
g = 9.8[m/s^2];
%}

eff = .6;
Pin = 100;
M = 100;
H = 5;
G = 9.8;

%Calculate Power Out[W]
Pout = eff * Pin;

%Calculate Energy[J]
E = M*G*H;

%Calculate Time[s]
T = E/Pout;
