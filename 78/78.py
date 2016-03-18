#!/usr/bin/python

'''
0 1
1 1
2 2
3 3
4 5
5 7
6 11
7 15
8 22
9 30
10 42

p(n) = p(n-1) + p(n-2) - p(n-5) - p(n-7) + ... (where ... = inifinity) p(-x) = 0

p(1) = p(0) = 1
p(2) = p(2 - 1) + p(2 - 2) = p(1) + p(0) = 1 + 1 = 2
p(3) = P(3 - 1) + p(3 - 2) = p(2) + p(1) = 2 + 1 = 3
p(4) = p(

p(n) = sum_{k=1}^n (-1)^{k+1} [ p(n - frac{1}{2} k (3k -1)) + p(n - frac{1}{2} k (3k+1)) ]

p(1) = sum_{k=1}^n (-1)^{1+1} [ p(n - frac{1}{2} (3 -1)) + p(n - frac{1}{2} (3+1)) ]
p(1) = [ p(1 - 1) + p(1 - 2) ]
p(1) = [ p(0) + p(-1) ]
p(1) = p(0) + p(-1)
p(1) = 1 + 0 

p(n) = sum_{k=1}^n (-1)^{k+1} [ p(n - frac{1}{2} k (3k -1)) + p(n - frac{1}{2} k (3k+1)) ]

'''

'''
import sys
depth = 1000000
sys.setrecursionlimit(depth)
n = 1;
d = {}

def Partition(sumy, largest):
    if (largest == 0):
        return 0
    if (sumy == 0):
        return 1
    if (sumy < 0):
        return 0

    useLargest = (sumy - largest, largest)
    notUseLargest = (sumy, largest - 1)
    if (useLargest not in d):
        d[useLargest] = Partition(sumy - largest, min(largest, sumy - largest + 1))
    if (notUseLargest not in d):
        d[notUseLargest] = Partition(sumy, largest - 1)

    return d[useLargest] + d[notUseLargest]
def Partition(sumy, largest, n):

    m = [[0 for x in range(n + 1)] for y in range(n + 1)] 

    for i in range(1, n+1):
        m[i][0] = 0;
    for i in range(1, n+1):
        m[0][i] = 1;

    for i in range(1, n + 1):
        for j in range(1, n + 1):
            if (i-j<0):
                m[i][j] = m[i][j-1];
                continue;
            m[i][j] = m[i][j-1] + m[i-j][j];

    return m[sumy][largest]
        
def GetPn(n):
    return Partition(n,n)
'''

n = 1;

pToPn = {}
pToPn[0] = 1
arr = list(range(1000000))
arr[0] = 1

'''
def P(n):
    if (n < 0):
        return 0

    total = 0


    if n not in pToPn:
        multiplier = 1
        for k in range(1, n + 1):
            #total += multiplier * (P(n - (k * (3 * k - 1)) // 2))
            #total += multiplier * (P(n - (k * (3 * k + 1)) // 2))
            in1 = n - (k * (3 * k - 1)) // 2
            in2 = n - (k * (3 * k + 1)) // 2
            if (in1 >= 0):
                total += multiplier * (pToPn[in1])
            if (in2 >= 0):
                total += multiplier * (pToPn[in2])
            multiplier *= -1

        pToPn[n] = total

    return pToPn[n]
'''

def P(n):
    total = 0
    multiplier = 1

    for k in range(1, n + 1):
        #total += multiplier * (P(n - (k * (3 * k - 1)) // 2))
        #total += multiplier * (P(n - (k * (3 * k + 1)) // 2))
        in1 = n - (k * (3 * k - 1)) // 2
        in2 = n - (k * (3 * k + 1)) // 2
        if (in1 >= 0):
            total += multiplier * (arr[in1])
        if (in2 >= 0):
            total += multiplier * (arr[in2])
        multiplier *= -1

    arr[n] = total

    return arr[n]

while True:
    Pn = P(n)
    #if (Pn % 100 == 0):
    print ("N: " + str(n) + "   P(N): " + str(Pn))
    #print ("N: " + str(n)),
    if (Pn % 1000000 == 0):
        print ("Answer found!!!")
        print ("N: " + str(n) + "   P(N): " + str(Pn))
        #print("P(N): " + str(Pn))
        break;
    #if (n >= 10000):
        #break;
    n += 1

