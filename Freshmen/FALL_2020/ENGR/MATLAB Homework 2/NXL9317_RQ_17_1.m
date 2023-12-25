%{

Name: Nghia Lam 
ID: 1001699317

Chapter 17 Question 1

Write a program that will ask the user to input the mass
of a cube of solid gold in units of [kg]

The output is length [in].

SG = 19.3
dW = .001 [kg/cm^3] 
Den = SG*dW
Den = goldM/v
l = cubed root (v)

%}
clc 

SG = 19.3;
dW = .001;

%Ask and shows the value of inputed mass [kg]
goldM = input('Enter the mass of the cube [kilograms]: ');
fprintf('\n%d',goldM);

%Get density [kg/cm^3]
Den = SG*dW;

%Get volume [cm^3]
v = goldM/Den;

%Get length [cm]
len = nthroot(v,3);

%Convert [cm]-->[in]
lenFinal = len * (1/2.54);

%Printing it out
fprintf('\nThe length of one side of the cube is %0.2f inches.',lenFinal);