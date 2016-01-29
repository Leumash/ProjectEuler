A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?






I want the millionth way to do this

0
1 2 3 4 5 6 7 8 9
Ways: 362880

1
0 2 3 4 5 6 7 8 9
Ways: 362880

Total ways thus far: 725760
Number must be 2




Looking for position 274240

20
1 3 4 5 6 7 8 9
Ways: 40320

...

26
0 1 3 4 5 7 8 9

Total ways thus far: 725760 + 241920
Number must be 27





Looking for position 32320

271
0 3 4 5 6 8 9
Ways: 5040

...

276
0 1 3 4 5 8 9

Total ways thus far: 725760 + 241920 + 30240
Number must be 278
Remainder 0 1 3 4 5 6 9





Looking for position 2080

2780
1 3 4 5 6 9
Ways: 720

2781
Ways: 720
0 3 4 5 6 9

Total ways thus far: 725760 + 241920 + 30240 + 1440
Number must be 2783
Remainder 0 1 4 5 6 9




Looking for position 640

27830
1 4 5 6 9
Ways: 120

...

27836
0 1 4 5 9
Ways: 120

Total ways thus far: 725760 + 241920 + 30240 + 1440 + 600
Number must be 27839
Remainder 0 1 4 5 6





Looking for position 40

278390
1 4 5 6
Ways: 24

Total ways thus far: 725760 + 241920 + 30240 + 1440 + 600 + 24
Number must be 278391
Remainder 0 4 5 6




Looking for position 16

2783910
4 5 6
Ways: 6

2783914
0 5 6
Ways: 6

Total ways thus far: 725760 + 241920 + 30240 + 1440 + 600 + 24 + 12
Number must be 2783915
Remainder 0 4 6




Looking for position 4

27839150
4 6
Ways: 2

Total ways thus far: 725760 + 241920 + 30240 + 1440 + 600 + 24 + 12 + 2
Number must be 27839154
Remainder 0 6




Looking for position 2

278391540
6
Ways: 1

Total ways thus far: 725760 + 241920 + 30240 + 1440 + 600 + 24 + 12 + 2 + 1
Number must be 278391546
Remainder 0


Looking for position 1

2783915460

