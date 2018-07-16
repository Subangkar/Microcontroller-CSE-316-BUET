clear all
xre = [ 204 455 12 411 -265 25 -255 125 -53 269 -51 136 -36 255 201 309 268 -141 61 -261 -51 187 -58 254 -35 25 195 150 397 132 204 -232 ];
P = [ 0 5 16 7 3 22 4 3 3 3 4 11 3 16 18 13 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
t = linspace(0,0.000050,32);
f = linspace(0,10000,17);
figure(1)
plot(t,xre)
figure(2)
plot(f,P(1:17))
