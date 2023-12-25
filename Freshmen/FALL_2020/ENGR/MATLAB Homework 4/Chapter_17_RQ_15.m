%{

Name: Nghia Lam 
ID: 1001699317

Chapter 17 Review Question 15

Q = Energy (Q)[J]
T = Temp (T)[K]
%}
clc 
clear
close all

Q = [12 17 25 40 50 58];
T = [1.5 2 3.25 5 6.25 7];

plot(Q,T,'rs','MarkerFaceColor','r','MarkerSize',15);
grid on
xlabel('Heat Applied (Q)[J]');
ylabel('Temp Change (T)(K)');
axis([0 70 0 8]);
hold on

%{
y =   m   * x +   b
T =   C1  * Q +   C2
T = .1220 * Q + .0578
%}
C = polyfit(Q,T,1); 
m = C(1);
b = C(2);

Qpf = [12:5:58];
Tpf = m*Qpf+b;
plot(Qpf,Tpf,'--r','LineWidth',3);

TF = sprintf('T = %0.3fQ+%0.3f',m,b);
text(30,2,TF,'EdgeColor','r','Color','r','FontSize',14);
