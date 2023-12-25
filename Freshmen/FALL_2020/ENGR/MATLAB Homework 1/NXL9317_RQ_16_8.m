%{

Name: Nghia Lam 
ID: 1001699317

Chapter 16 Question 8

Determine how far the Microjoule will travel in kilometers
given a user-specified amount of ethanol,
provided in units of grams?

What is distance[km]

10705 [mi/gal]
M = 100[g]
SG = .789
denW = 8.35[lbm/gal]

%}

M = 100;
SG = .789;
FPower = 10705;
DenW = 8.35;

%Get density [lbm/gal]
Den = SG * DenW;

%Convert Density[lbm]-->[kg]-->[g]
Den = Den * (1/2.205) * (1000/1);

%Get Volume [gal]
V = M/Den;

%Multiply volume by performance to get distance [mi]
Dist = FPower * V;

%Convert distance[mi]-->[km]
Dist = Dist *(1/.621);