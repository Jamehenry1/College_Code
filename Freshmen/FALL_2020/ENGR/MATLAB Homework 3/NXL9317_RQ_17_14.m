%{

Name: Nghia Lam 
ID: 1001699317

Chapter 17 Question 14

VehicleSpeed = (v)[mph]
Reaction = (d)[m]
Braking = (d)[m]

%}
clc 
clear

%Values
VehicleSpeed = [20 30 40 50 60 70];
Reaction = [6 9 12 15 18 21];
Braking = [6 14 24 38 55 75];

%Write a for loop so that I don't have to add every distance
for i = 1:1:6
    TotalDistance(i) = Reaction(i)+Braking(i);
end

title('Distance covered when Braking and Reacting at a certain Velocity')
plot(TotalDistance,VehicleSpeed,'ko','MarkerFaceColor','k');
xlabel('Distance(d)[m]');
ylabel('Vehicle Speed(v)[mph]');

axis([0 100 0 100])
grid on





    
    