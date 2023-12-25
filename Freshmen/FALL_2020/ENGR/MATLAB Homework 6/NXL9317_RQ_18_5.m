%{

Name: Nghia Lam 
ID: 1001699317

Chapter 18 Review Question 5

Question:
A program that will ask the user to input the mass of a cube 
of solid gold in units of kilograms and display the length of a 
single side of the cube in units of inches.

SG = Specific gravity of gold
pW = density of water 1000[kg/m^3]
p = density [kg/m^3]
m = mass [kg]
V = volume [m^3]
l = length [m] --> [in]

%}
clc 
clear 
close all

m = input('Enter the mass of the cube [kilograms]: ');

if m < 0 || m == 0
    error('Mass must be grater than zero grams.');
end

%SG = p/pW --> p = SG*pW
SG = 19.3;
pW = 1000;
p = SG*pW;

%p = m/V --> V = m/p
V = m/p;
l = nthroot(V,3);

% [m] --> [cm] --> [in]
l = l*100*(1/2.54);

fprintf('\nThe length of one side of the cube is %.2f inches\n',l);






