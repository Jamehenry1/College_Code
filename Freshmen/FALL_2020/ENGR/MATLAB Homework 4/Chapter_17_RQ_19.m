%{

Name: Nghia Lam 
ID: 1001699317

Chapter 17 Review Question 15

G = Gear size [G][mm]
T = Time (T)[year]

%}
clc 
clear
close all

T = [0 5 7 16 25 31 37];
G = [.8 .4 .2 .09 .007 2E-04 8E-06];

plot(T,G,'gs','MarkerFaceColor','g','MarkerSize',13);
axis([0 40 0 1]);
xlabel('Time (T)[year]');
ylabel('Gear size [G][mm]');

grid on 
hold on


%{
y = be^(mx) --> ln(y) = mx + ln(b)

%}

C = polyfit(T,log(G),1);

m = C(1);
b = exp(C(2));

Tpf = [0:1:37];
Gpf = b*exp((m*Tpf));

plot(Tpf,Gpf,'--g');

TF = sprintf('G = %.3fe^{%.3fT}',b,m);
text(20,.2,TF,'EdgeColor','g','Color','g','FontSize',14);




