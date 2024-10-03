W = poly([1],'s', 'c') / poly([1 2 1.5 1],'s', 'c');

M = syslin('c', W);
plot(csim('step', 0:0.01:10, M));
plot(roots(poly([1 2 1.5 1],’s’,’c’)))
xgrid();
nyquist(M);
bode(M);
