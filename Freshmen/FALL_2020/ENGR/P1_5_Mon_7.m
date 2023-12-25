%{
Project 
Team Name: 5 Mon 7
Names: Nghia Lam, Kevin Martinez, Eijiah Williams
%}
clc
clear

%Fixed Cost-----------------------------------------------------------
%{
    A = total surface area[ft^2]
Values: 
    (1)Material 
    (2)Thickness of Wall[in]
    (3)Material cost[$/ft^3]
    (4)Miscellaneous Construction Materials[$]
    (5)Labor Cost[$/(person week)]
    (6)Number of Laborers(people)
    (7)Number of weeks of construction
%}
A = 3000;
Mat = {'Concrete',16,30,96000,900,5,5;
       'Wood',23,53,115000,800,12,11;
       'Adobe',18,42,68000,600,6,5};

Choice = menu('Materials',Mat{:,1});


%Operational Variable Cost--------------------------------------------
%{
    ECost = Energy Cost[$/week]
    lCost = Labor Cost[$/week]
    mCost = Maintenace Cost[$/week]
    ldCost = Landfill Cost[$/week]
    numW = Number of weeks per year the zoo will operate
    numY = Number of years the zoo will operate
%}
ECost = input('Energy Cost[$/week]: ');
lCost = input('Labor Cost[$/week]: ');
mCost = input('Maintenace Cost[$/week]: ');
ldCost = input('Landfill Cost[$/week]: ');
numW = input('Number of weeks per year: ');
numY = input('Number of year the zoo will operate: ');


%Donations and public interest--Used to calculate revenue-------------
%{
    pCost = Price of admission per person [$/person]
    numP = Number of people per week that will visit the zoo
    dMoney = Expected donations per week [$/week]
%}
pCost = input('Price of Admission[$/person]: ');
numP = input('Number of people per week: ');
dMoney = input('Donations[$/week]: ');


%Breakeven Analysis--------------

%Total Fixed Cost to construct enclosure(Construction Cost)[$]:
tFixC = ((cell2mat(Mat(Choice,2))/12)*cell2mat(Mat(Choice,3))*A)+cell2mat(Mat(Choice,4))+(cell2mat(Mat(Choice,5))*cell2mat(Mat(Choice,6))*cell2mat(Mat(Choice,7)));

%Total Varible Cost of operating the enclosure per week[$/week]:
tVarWC = ECost+lCost+mCost+ldCost;

%Total Varible Cost of operating the enclosure for determined year(Vector it)[$/year]:
yearVec = 0:numY;
tVarYC = yearVec*numW*tVarWC;

%Total Revenue Year(Vector)[$/year]
tRevY = yearVec*numW*((pCost*numP)+dMoney);

%Total Profit Year(Vector)[$/year]
tProfitY = tRevY - (tVarYC + tFixC);

%BreakEven point[month]
tVarMC = tVarYC(2)/12;
tRevM = tRevY(2)/12;

y = @(x) tRevM*x - tVarMC*x - tFixC;
x0 = 1;
mBreP = fzero(y,x0);

%Donation Break Money[$]
dBreM = -1*(tRevM*7 - tVarMC*7 - tFixC);

%Printing
fprintf('\nMaterial: %s',char(Mat(Choice,1)));
fprintf('\n\tOperating %d weeks per year will generate per year', numW);
fprintf('\n\t\tRevenue: \t$%d',tRevY(2));
fprintf('\n\t\tCost: \t\t$%d',tVarYC(2));
fprintf('\n\tThe breakeven time is %.2f months',mBreP);
fprintf('\n\tThe total profit after %d years is $%.3e\n',numY,tProfitY(numY));


%Getting point of intercept Plot 1
xCordInt = mBreP/12;
yCordInt = xCordInt*tRevY(2); 

%Plot 1
f1 = figure;

plot(yearVec,tRevY,yearVec,tVarYC+tFixC,'--',xCordInt,yCordInt,'ok','MarkerFaceColor','k','MarkerSize',8);
grid on
axis([0 numY 0 inf]);
xlabel('Number of Years[y]')
ylabel('Amount of Money[$]')
title('Tota; Amount of Revenue and Cost Per Year')
legend('Revenue','Cost','Breakeven','Location','best')

%Getting point of intercept Plot 2
yCordInt2 = 0;

%Plot 2
f2 = figure;
plot(yearVec,tProfitY,xCordInt,yCordInt2,'ok','MarkerFaceColor','k','MarkerSize',8);
grid on 
axis([0 numY -inf inf]);
xlabel('Number of Year')
ylabel('Amount of Money[$]')
title('Total Amount of Profit Per Year')
legend('Profit','Breakeven','Location','best')







