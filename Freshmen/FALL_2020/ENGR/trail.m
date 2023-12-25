clear 
clc
Omega = [250 373 436 510 690];
E = [3130 6840 9200 13000 23800];

plot(E,Omega);
C = polyfit(log10(Omega),log10(E),1);
m = C(1);
b = 10^C(2);
E10M = 10000;

OP = nthroot(E10M/b,m);