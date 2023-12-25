%{

Name: Nghia Lam 
ID: 1001699317

Chapter 17 Question 10
Convert the initial temperature [deg F] to other temperature 
TempF = [deg F]

%}
clc

%Initial temperature [deg F]
TempF = input('\nEnter the temperature [deg F]: ');

%Converting the initial temperature into [deg C], [K], and [deg R]
FinishedTemp = [(TempF-32)/1.8,((TempF-32)/1.8)+273 ,(TempF + 460)];

%Creating a cell for a menu and choosing which unit system to convert to
TempType = {'deg C' 'K' 'deg R'};
Choice = menu('Choose a final unit',TempType(1,:));

%Putting the chosen unit system into a variable 
TempConv = FinishedTemp(Choice);

%Printing it out 
fprintf("\nThe equivalent temperature to %0.2f deg F is %0.2f\n", TempF, TempConv);




