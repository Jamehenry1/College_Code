%{

Name: Nghia Lam 
ID: 1001699317

Chapter 18 Review Question 8

SG = .789
p = density [g/cm^3]
pW = density of water [g/cm^3] 
m = mass [g]
d = distance [mi] --> [km]
Eff = 10705 [mi/gal]
%}
clc 
clear 
close all

Eff = 10705;
SG = .789;
pW = 1;

m = input('Enter mass of ethanol[grams]: ');
if(m < 0 || m > 500)
    error('Mass must be between 0 and 500 grams');
end
%Calculating density[g/cm^3]
p =(SG/pW);

%Calculating Volume[cm^3] --> [L] --> [gal]
V = 100/p/1000;
V = V*.264;

%Calculating Distance[mi] --> [km]
d = Eff*V;
d = d/.621;

fprintf('The distance the Microjoule traveled is %.0f kilometers\n',d);






