%{
A = [1 2];

RUN = [1 2 8 ;
       4 5 7 ; 
       7 8 9 ];

E1 =  RUN(1:2,:)'.*A;

CPM = [1 2 3];
NM = [4 5 6];

EPP = CPM .* NM;
EPP_total = EPP .* RUN;
%}
%{
M = [-5 3 3 75;
     3 -5 75 3;
     3 75 -5 3;
     75 3 3 -5];
I = [1:.1:4];
z = .9;

B = 60 * I.^(exp(-z*I));

[a,b] = max(B);
%}
%{
A1 = [3 4; 5 6; 7 8; 9 10];
B1 = [11 12; 13 14; 15 16; 17 18];
MatrixList = {'A1', 'B1'};
%}
%{
name = input('Enter your name:', 's');
choice = menu('Do you live in South Carolina?','Yes','No');
BDay = input('What is your B day in [month day year]:');

yearDif = 2020 - BDay(3);
fprintf('\n%s was born on %d-%d-%d\n', name, BDay(1),BDay(2),BDay(3));

fprintf('\nHe was born %d years ago\n',yearDif);

%}
%{
V = 10;
n = V/(.08206* 300);
g = n * 28;
%}
V = 10;
g = 10;
mw = 32;
n = g/mw;
T = V/(.08206* n);
T = T -273;