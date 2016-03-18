#!/usr/bin/python

n = 1;
arr = list(range(1000000))
arr[0] = 1

def P(n):
    total = 0
    multiplier = 1

    for k in range(1, n + 1):
        in1 = n - (k * (3 * k - 1)) // 2
        in2 = n - (k * (3 * k + 1)) // 2
        if (in1 >= 0):
            total += multiplier * (arr[in1])
        if (in2 >= 0):
            total += multiplier * (arr[in2])
        multiplier *= -1
        if (in1 < 0):
            break;

    arr[n] = total % 10000000

    return arr[n]

while True:
    Pn = P(n)
    if (Pn % 1000000 == 0):
        print (n)
        break;
    n += 1

