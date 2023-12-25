%{

Name: Nghia Lam 
ID: 1001699317

Chapter 17 Review Question 16

R = Radius (R)[cm]
H = Height (H)[cm]

%}
clc 
clear
close all

R = [.01 .05 .1 .2 .4 .5];
H = [14 3 1.5 .8 .4 .2];
plot(R,H,'bs','MarkerFaceColor','b','MarkerSize',15);
grid on
axis([0 .6 0 15])
xlabel('Radius (r)[cm]');
ylabel('Height (H)[cm]');
hold on
%{
y = bx^m --> ln(y = bx^m)

%}
C = polyfit(log(R),log(H),1);
m = C(1);
b = exp(C(2));

Rpf = [.011:.02:.5];
Hpf = b*Rpf.^m;
plot(Rpf,Hpf,'--b','LineWidth',3);

TF = sprintf('H = %.3fR^{%.3f}',b,m);
text(.3,5,TF,'EdgeColor','b','Color','b','FontSize',14);

