%{

ICA 18-17, pg.766
Blood pressure example

%}

clear 
clc
close all

A = input('Enter your age: ');
SP = input('Enter your Systolic Blood Pressure: ');
DP = input('Enter your Diastolic Blood Pressure: ');

if A < 15 || A > 24
    fprintf('Result = DO Not Use\n');
    error('Age is outside range. Program terminating');
elseif A < 19 && A > 15
    if SP > 120 || DP > 81
        fprintf('Result = HighBlood Pressure\n')
    else
        fprintf('Normal Blood Pressure\n')
    end
elseif A > 20 || A < 24
    if SP > 132 || DP > 83
        fprintf('Result = HighBlood Pressure\n')
    else
        fprintf('Normal Blood Pressure\n')
    end
end
