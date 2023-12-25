%{

Name: Nghia Lam 
ID: 1001699317

Chapter 18 Review Question 11

Determine whether a user specified altitude [meter]
is in the troposphere, lower stratosphere, 
or upper stratosphere

H = Altitude [m]
T = Temp [degrees C]
P = Pressure [kPa]

TroS = Troposhere: Altitude (H < 11,000) [m]

LowStr = Lower Stratosphere: Altitude (11,000 <= H < 25,000) [m]

UpStr = Upper Stratosphere: Altitude (25,000 <= H 50,000) [m]
%}
clc
clear 
close all

H = input('Enter Altitude [m] in between the range of 0 and 50,000 : ');
T = 0;
P = 0;

if H >= 50000 || H < 0
    error('Your Altitude is out of range')
else
    if H < 11000
        
        T = 15.04 - .00649*H;
        P = 101.29*((T+273.1)/288.08)^5.256;
        fprintf('An altitude of %.0f is in the troposhere with a temperature of %.0f C and pressure of %.0f kPa\n',H,T,P);
    
    elseif H >= 11000 && H < 25000
        
        T = -56.46;
        P = 22.65*exp(1.73-.000157*H);
        fprintf('An altitude of %.0f is in the Lower Stratosphere with a temperature of %.0f C and pressure of %.0f kPa\n',H,T,P);
        
    else
        
        T = -131.21 + .00299*H;
        P = 2.488*((T+273.1)/216.6)^-11.388;
        fprintf('An altitude of %.0f is in the Upper Stratosphere with a temperature of %.0f C and pressure of %.0f kPa\n',H,T,P);
        
    end
end



