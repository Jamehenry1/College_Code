%{

Name: Nghia Lam 
ID: 1001699317

Chapter 17 In Class Assignment 24

Ci = initial amount (m)[g]
k = hours (T)[h]
T = Time (T)[h]

Cf = final amount (m)[g]

%}
clc 
clear

%Time[h]
T = [0 1 2 3 4 5];
k = 1.48;

%Amount of grams of Isotope[g]
Ci = 10;

%Looping for isot
for i = 1:1:6
    Cf(i) = Ci*exp((-T(i))/k);
end

plot(T,Cf)
title('Decay of Isotope Over Time')
xlabel('Time(T)[h]')
ylabel('Isotope amount(m)[g]')
grid on

axis([0 5 0 10])






