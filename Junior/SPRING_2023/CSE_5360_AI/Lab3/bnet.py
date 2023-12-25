import sys
# Nghia Lam
# 1001699317

'''

0-B: True if there is a Baseball Game on TV, False if not
1-G: True if George watches TV, False if not
2-C: True if George is out of Cat Food, False if not
3-F: True if George feeds his cat, False if not.

'''

B = 0
G = 1
C = 2
F = 3

class BaseTable:
    def __init__(self,t,f):
        self.t = t 
        self.f = f 
        self.tProb = t/365
        self.fProb = f/365

class Condition1Table:
    def __init__(self,tt,tf,ff,ft,count0,count1):
        self.tt = tt 
        self.tf = tf
        self.ff = ff 
        self.ft = ft
        #self.ttProb = tt/count1
        #self.tfProb = tf/count1
        #self.ffProb = ff/count0
        #self.ffProb = ft/count0
        self.countT = count1
        self.countF = count0
        self.tProb = [tt/count1,tf/count1]
        self.fProb = [ft/count0,ff/count0]

class Condition2Table:
    def __init__(self,ttt,ttf,tft,tff,ftt,ftf,fft,fff,count00,count01,count10,count11):
        self.ttt = ttt
        self.ttf = ttf
        self.tft = tft
        self.tff = tff
        self.ftt = ftt
        self.ftf = ftf
        self.fft = fft
        self.fff = fff
        
        self.countTT = count11
        self.countTF = count10
        self.countFT = count01
        self.countFF = count00

        self.ttProb = [ttt/count11,ttf/count11]
        self.tfProb = [tft/count10,tff/count10]
        self.ftProb = [ftt/count01,ftf/count01]
        self.ffProb = [fft/count00,fff/count00]

# this will calculate the true and false for the values
def cal(array,col):
    t = 0
    f = 0

    for i in range(len(array)):
        if array[i][col] == 1:
            t = t + 1
        else:
            f = f + 1
    
    return BaseTable(t, f)

# Class for Condition with one variable
def calBase2(array,colEffect,colCause):
    ff = 0
    ft = 0
    tf = 0
    tt = 0
    count0 = 0
    count1 = 0
    for i in range(len(array)):
        if array[i][colCause] == 0:
            if array[i][colEffect] == 0:
                ff = ff + 1
            if array[i][colEffect] == 1:
                ft = ft + 1
            count0 = count0 + 1
        
        elif array[i][colCause] == 1:
            if array[i][colEffect] == 0:
                tf = tf + 1
            if array[i][colEffect] == 1:
                tt = tt + 1
            count1 = count1 + 1
        

    #print(str(tt/count1) + " " + str(tf/count1))
    #print(str(ft/count0) + " " + str(ff/count0))
    #print(count1)
    #print(count0)

    return Condition1Table(tt,tf,ff,ft,count0,count1)

# Class for Condition wiht 2 variable
def calBase3(array,colEffect,colCause,colCause2):
    ttt = 0
    ttf = 0

    tft = 0
    tff = 0

    ftt = 0
    ftf = 0

    fft = 0
    fff = 0

    count00 = 0
    count01 = 0
    count10 = 0
    count11 = 0

    for i in range(len(array)):
        if array[i][colCause] == 0 and array[i][colCause2] == 0:
            if array[i][colEffect] == 0:
                fff = fff + 1
            if array[i][colEffect] == 1:
                fft = fft + 1
            count00 = count00 + 1
        if array[i][colCause] == 0 and array[i][colCause2] == 1:
            if array[i][colEffect] == 0:
                ftf = ftf + 1
            if array[i][colEffect] == 1:
                ftt = ftt + 1
            count01 = count01 + 1
        if array[i][colCause] == 1 and array[i][colCause2] == 0:
            if array[i][colEffect] == 0:
                tff = tff + 1
            if array[i][colEffect] == 1:
                tft = tft + 1
            count10 = count10 + 1
        if array[i][colCause] == 1 and array[i][colCause2] == 1:
            if array[i][colEffect] == 0:
                ttf = ttf + 1
            if array[i][colEffect] == 1:
                ttt = ttt + 1
            count11 = count11 + 1

    #print(str(ttt/count11) + " " + str(ttf/count11))        
    #print(str(tft/count10) + " " + str(tff/count10))
    #print(str(ftt/count01) + " " + str(ftf/count01))
    #print(str(fft/count00) + " " + str(fff/count00))

    return Condition2Table(ttt,ttf,tft,tff,ftt,ftf,fft,fff,count00,count01,count10,count11)

# Print for Task 1 here
def PrintTable(bBase,cBase,gBase,fbase):
    print('| B Table ------------------ ')
    print('|        |   {:3}  |   {:3}  |'.format("Bt","Bf"))
    print('|   B    | {:.4} | {:.4} |\n'.format(bBase.tProb,bBase.fProb))
    #print("Bt: ",bBase.tProb, "Bf: ",bBase.fProb)
    #print("Gt: ",gBase.tProb, "Gf: ",gBase.fProb)
    print('| C Table ------------------ ')
    print('|        |   {:3}  |   {:3}  |'.format("Ct","Cf"))
    print('|   C    | {:.4} | {:.4} |\n'.format(cBase.tProb,cBase.fProb)) 
    
    #print("Ft: ",fBase.tProb, "Ff: ",fBase.fProb)

    print('| G Table -------------------------- ')
    print('|   B    |   {:3}  |   {:3}  |'.format("P(Gt|B)","P(Gf|B)"))
    print('|   T    |   {:.4}   |   {:.3}   |'.format(gBase.tProb[0],gBase.tProb[1]))
    print('|   F    |   {:.4}   |   {:.4}   |\n'.format(gBase.fProb[0],gBase.fProb[1]))
    
    print('| F Table --------------------------- ')
    print('| G | C |  {:3}  |  {:3}  |'.format("P(Ft|G,C)","P(Ff|G,C)"))
    print('| T | T |   {:.3}    |   {:.4}    |'.format(fbase.ttProb[0],fbase.ttProb[1]))
    print('| T | F |   {:.4}    |   {:.4}    |'.format(fbase.tfProb[0],fbase.tfProb[1]))
    print('| F | T |   {:.4}    |   {:.4}    |'.format(fbase.ftProb[0],fbase.ftProb[1]))
    print('| F | F |   {:.4}    |   {:.3}    |\n'.format(fbase.ffProb[0],fbase.ffProb[1]))
    print("FT", fbase.ftProb)
    print("FF", fbase.ffProb)
    
#Calculates Task 2 here 
def ProbCal(bBase,cBase,gBase,fbase):

    if len(sys.argv) == 6:
        Bdata = sys.argv[2]
        Gdata = sys.argv[3]
        Cdata = sys.argv[4]
        Fdata = sys.argv[5]

    probCalInput = []

    if Bdata == 'Bt':
        probCalInput.append(bBase.tProb)
    else: 
        probCalInput.append(bBase.fProb)
    
    if Gdata == 'Gt' and Bdata == "Bt":
        probCalInput.append(gBase.tProb[0])
    elif Gdata == 'Gt' and Bdata == "Bf":
        probCalInput.append(gBase.fProb[0])
    elif Gdata == 'Gf' and Bdata == "Bt":
        probCalInput.append(gBase.tProb[1])
    elif Gdata == 'Gf' and Bdata == "Bf":
        probCalInput.append(gBase.fProb[1])

    if Cdata == 'Ct':
        probCalInput.append(cBase.tProb)
    else:
        probCalInput.append(cBase.fProb)

    if Gdata == 'Gt' and Cdata == 'Ct' and Fdata == 'Ft':
        probCalInput.append(fbase.ttProb[0])
    elif Gdata == 'Gt' and Cdata == 'Ct' and Fdata == 'Ff':
        probCalInput.append(fbase.ttProb[1])
    elif Gdata == 'Gt' and Cdata == 'Cf' and Fdata == 'Ft':
        probCalInput.append(fbase.tfProb[0])
    elif Gdata == 'Gt' and Cdata == 'Cf' and Fdata == 'Ff':
        probCalInput.append(fbase.tfProb[1])
    elif Gdata == 'Gf' and Cdata == 'Ct' and Fdata == 'Ft':
        probCalInput.append(fbase.ftProb[0])
    elif Gdata == 'Gf' and Cdata == 'Ct' and Fdata == 'Ff':
        probCalInput.append(fbase.ftProb[1])
    elif Gdata == 'Gf' and Cdata == 'Cf' and Fdata == 'Ft':
        probCalInput.append(fbase.ffProb[0])
    elif Gdata == 'Gf' and Cdata == 'Cf' and Fdata == 'Ff':
        probCalInput.append(fbase.ffProb[1])

    #for i in range(len(sys.argv)):
    #   print(sys.argv[i])

    #print(probCalInput)

    prob = probCalInput[0] * probCalInput[1] * probCalInput[2] * probCalInput[3] 
    print("-----------------------------------------------------------------------------------")
    print(str(probCalInput[0]) + " * " +str(probCalInput[1])+ " * " +str(probCalInput[2])+ " * " +str(probCalInput[3]))
    print("-----------------------------------------------------------------------------------")
    print("The answer for "+ sys.argv[2] + " " + sys.argv[3] + " " + sys.argv[4] + " " + sys.argv[5] + ": " + str(prob))

def main():

    #print(len(sys.argv))

    fileName = sys.argv[1]

    with open(fileName) as f:
        #w, h, g, b = [int(x) for x in next(f).split()] # read first line
        array = []
        for line in f: # read rest of lines
            array.append([int(x) for x in line.split()])
    
    # Creates the objects and puts data of each table in them
    bBase = cal(array,B)
    cBase = cal(array,C)
    gBase = calBase2(array,G,B)
    fbase = calBase3(array,F,G,C)

    # bnet.py <training_data> <Bt/Bf> <Gt/Gf> <Ct/Cf> <Ft/Ff>
    if len(sys.argv) == 6:
        ProbCal(bBase,cBase,gBase,fbase)
    else:
        PrintTable(bBase,cBase,gBase,fbase)

main()