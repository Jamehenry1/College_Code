%{

Name: Nghia Lam 
ID: 1001699317

Chapter 18 Review Question 12

Determine whether a given Mach number is 
subsonic, transonic, supersonicc, or hypersonic

Speed = [m/s]
Mach = 1 [m/s] 
MachT = Speed/Mach

%}
clc
clear
close all

Speed = input('Enter your speed in meters per seconds [m/s]: ');
if Speed < 0
    error('You have entered a negitive number');
end
Mach = 1;
MachT = Speed/343;

if MachT < Mach
    fprintf('Subsonic, Mach number is %.2f\n',MachT);
elseif MachT == Mach
    fprintf('Transonic, Mach number is %.2f\n',MachT);
elseif MachT > Mach && MachT < (Mach * 5)
    fprintf('Supersonic, Mach number is %.2f\n',MachT);
else 
    fprintf('Hypersonic, Mach number is %.2f\n',MachT);
end






