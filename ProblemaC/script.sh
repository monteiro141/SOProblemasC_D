gcc -Wall -lm PC.c
./a.out <input.txt > oo1
./a.out <input2.txt > oo2
./a.out <input3.txt > oo3
./a.out <input4.txt > oo4
./a.out <input5.txt > oo5

diff oo1 so1 > dif1
diff oo2 so2 > dif2
diff oo3 so3 > dif3
diff oo4 so4 > dif4
diff oo5 so5 > dif5

rm oo1 oo2 oo3 oo4 oo5
