%{
Nghia Lam 

Example 2: 8.3 ER3
 
v = 2.5 [gal]
sg = 1.315
pw = 8.35[lbm/gal]
g = 3.7 [m/s^2]

p = sg * pw
m = p * v --> lbm

Find Weight in [lbf]
%}

v = 2.5;
g = 3.7;
sg = 1.315;
pw = 8.35;

%calculate for Density [lbm/gal]
p = sg * pw;

%calculate for Mass [lbm]
m = p * v;

%convert Mass [lbm] --> [kg]
m = m * 1/2.205;

%calculate for Weight [N]
w = m * g;

%convert Weight [N] --> [lbf]
w = w * .225/1;
