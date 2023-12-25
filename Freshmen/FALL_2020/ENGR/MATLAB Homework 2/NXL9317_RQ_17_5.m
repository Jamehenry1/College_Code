%{

Name: Nghia Lam 
ID: 1001699317

Chapter 17 Question 5

Find how much heat you need to change the initial temperature to the finial
temperature, and write it in the a certain type of way.

%}
clc

%Name of character
name = input('Type in your first and last name with a space in between them: ','s');

%Get the day by using a menu
date = {'Monday' 'Wednesday' 'Friday'};
dateC = menu("Days of the Week", date(1,:));
day = date{dateC};

%Mass input and turn [g]-->[kg]
M_g = input('Mass [g]: ');
M_Kg = M_g * (1/1000); 

%Specific Heat
Cp = input('Specific Heat [J]/[kg][K]: ');

%Temperature of initial and final 
iTempF = input('Initial Temperature [Fahrenheit]: ');
fTempF = input('Final Temperature [Fahrenheit]: ');

%conversion from [F]-->[K]
iTempK = ((iTempF-32)/1.8) + 273; 
fTempK = ((fTempF-32)/1.8) + 273;

%Find Heat energy
Q = M_Kg * Cp * (fTempK - iTempK);

%Printing out the statement
fprintf('\n\n On %s, the user %s entered a %0.2f gram mass with a specific\n heat of %0.2f J/(kg K) that should be raised from %0.2f degrees\n Fahrenheit to %0.2f degrees Fahrenheit.\n This should require %0.1f J of heat to be added to the substance.\n', day, name, M_g, Cp, iTempF, fTempF, Q);




