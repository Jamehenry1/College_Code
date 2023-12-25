%{

Name: Nghia Lam 
ID: 1001699317

Chapter 18 Review Question 13

Determine the Color of the Wavelength 

Wave = Wavelength interval [nm]
C = color;
%}
clc 
clear 
close all

Wave = input('Enter your Wavelength interval (700-400)[nm]: ');
C = 'Color';
if Wave > 700 || Wave < 400
    error('You are out of the interval');
else
    if Wave <= 700 && Wave > 635
        C = 'Red';
    elseif Wave <= 635 && Wave > 590
        C = 'Orange';
    elseif Wave <= 590 && Wave > 560 
        C = 'Yellow';
    elseif Wave <= 560 && Wave > 490
        C = 'Green';
    elseif Wave <= 490 && Wave > 450
        C = 'Blue';
    else
        C = 'Violet';
    end
end

fprintf('Your color is %s on the Wavelength %d\n',C,Wave);



