%{

Name: Nghia Lam 
ID: 1001699317

Chapter 16 Question 9

What is mass of the oxygen gas?
What is Mass[g]?

MW = 32[g/mol]
V = 1.25[gal]
Temp = 125[Celsius]
Pres = 2.5[atm] 
R = .08206[atm L]/[mol K]


%}

MW = 32;
V = 1.25;
Temp = 125;
Pres = 2.5;
R = .08206;

%Convert Temp[C]-->[K]
Temp = Temp + 273;

%Convert V[gal]-->[L]
V = V *(1/.264);

%Get the amount of mols
n = (Pres * V)/(R*Temp);

%Get mass[g]
M = n * MW;

