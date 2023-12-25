%{
Name: Nghia Lam
UTA ID: 1001699317

r = radius[ft]

%}

clc
clear

%4*2 Cell of the lawns and measurements [acre]
lawn = {'Small', .10;
        'Standard', 1/6;
        'Medium', .25;
        'Large', .75};
Flawn = menu('Select one of your front lawns', lawn());
Rlawn = menu('Select one of your back lawns', lawn());

%total lawn size [m^2]; 1 acre = 4047 m^2; 1416/.35 = 4047; 
TLawnS = (cell2mat(lawn(Flawn,2))+cell2mat(lawn(Rlawn,2))) * 4047;

name = input('What is your name: ', 's');

%Number of sprinklers = Total Lawn Size / Watering area per sprinkler
r = 15;
%change radis [ft]-->[m] and calculate area;
WArea = pi * (r * 1/3.28)^2;
NumSpr =  TLawnS/ WArea;


%SprVol = Volume per min per sprinkler [L/min]-->[gal/min]
SprVol = 7.5 * .264;
%T = [min]
T = 15;
%Total Volume = Volume per sprinkler * Time water is run * Total number of sprinklers
TVol =  SprVol * T * NumSpr;

%total water cost [$/gal]
UCost = .0055;
TCost = UCost * TVol;

fprintf('For resident %s, ', name);
fprintf('owning a %.2f acre front lawn and a %.2f acre back lawn for a total lawn size of %.2f m^2, ', cell2mat(lawn(Flawn,2)),cell2mat(lawn(Rlawn,2)), TLawnS);
fprintf('it will require %.0f sprinklers to cover. ', NumSpr);
fprintf('The water cost will be $%f  each time they water their lawn.\n',TCost);

Wtr = [1360 2030 2260 3390 6780 10170; 10 16 17 22 32 41]; 

figure ('Color','w');
plot(Wtr(1,:),Wtr (2,:), 'sg', 'MarkerSize', 14, 'MarkerFaceColor', 'g');
grid on
axis([0 12000 0 50])
xlabel('Water Usage (V)[gal]', 'FontSize', 16,'FontWeight','bold')
ylabel('Number of Sprinklers (NS)[#]', 'FontSize', 16, 'FontWeight','bold')
