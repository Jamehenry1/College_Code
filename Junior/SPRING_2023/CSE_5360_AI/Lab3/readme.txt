Nghia Lam
1001699317

Python 3.10.7
Used VS Code to run this 

Structure:
    I have 3 classes that will hold the information of table that I have calcualted from the file
    - BaseTable -> just for calculation normaly
    - Condition1Table -> Holds calulation with 1 variable conditional prob
    - Condition2Table -> Holds calculation with 2 variable condition prob

    - def cal(array,col): -> calculates normally
    - def calBase2(array,colEffect,colCause): -> calculation conditions
    - def calBase3(array,colEffect,colCause,colCause2): -> calculates conditions with 2 variable 

    - def ProbCal(bBase,cBase,gBase,fbase): -> calcualtes probabilty of Task 2

How to run the Code:
    Outline: python bnet.py <training_data>
    - Task 1: python .\bnet.py .\training_data.txt
        This will show the table calculated via the file inputed

    Outline: python bnet.py <training_data> <Bt/Bf> <Gt/Gf> <Ct/Cf> <Ft/Ff>
    - Task 2: python .\bnet.py .\training_data.txt Bt Gf Ct Ff
        This wil show the calcualtions of P(<Bt/Bf> <Gt/Gf> <Ct/Cf> <Ft/Ff>)