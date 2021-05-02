gcc -Wall -lm main.c
a.out < si1 > oo1
a.out < si2 > oo2
a.out < si3 > oo3
a.out < si4 > oo4
a.out < si5 > oo5
a.out < si6 > oo6

diff so1 oo1
diff so2 oo2
diff so3 oo3
diff so4 oo4
diff so5 oo5
diff so6 oo6