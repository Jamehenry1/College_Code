%{

Name: Nghia Lam 
ID: 1001699317

Chapter 18 Review Question 22


%}
clc 
clear 
close all

grade = {'A', 'B', 'C', 'D', 'F'};

Choice = menu('Select the grade earned:',grade{1,:});

if(Choice == 1)
    gradeRange = '90 <= grade';
elseif(Choice == 2)
    gradeRange = '80 <= grade < 90';
elseif(Choice == 3)
    gradeRange = '70 <= grade < 80';
elseif(Choice == 4)
    gradeRange = '60 <= grade < 70';
elseif(Choice == 5)
    gradeRange = '0 <= grade < 60';
end

fprintf('If you earn the letter grade %s, your numeric grade is in the range: %s',grade{Choice},gradeRange);



