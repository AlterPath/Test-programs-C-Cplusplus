clear; clc; close all;
EbN0 = -5:0.1:5
BER=zeros(1,length(EbN0));
mnozh = 10.^(EbN0/20);
NN = 1000*(EbN0-EbN0(1)+1);
tic;
for n = 1:length(EbN0)
  sig = 2*randi([0,1])-1;
  display(sig)
 for k = 1:NN(n)
 shum = (randn(1,1)+1i*randn(1,1))/sqrt(2);
 spec = fft(mnozh(n)*sig+shum);
 phaza = angle(spec);
 as = angle(sig);
 if (abs(phaza) < pi/2)&&(abs(as) > pi/2) BER(n)=BER(n)+1; end
 if (abs(phaza) > pi/2)&&(abs(as) < pi/2) BER(n)=BER(n)+1; end
 end
end
toc;
semilogy(EbN0,(BER./NN)); grid; hold on;
semilogy(EbN0,1/2*(erfc(sqrt(10.^(EbN0/10)))),'--k'); hold off; %PSK
legend(['Imitation';'Theory']);
ylabel('BER'); xlabel('E_b/N_0, dB')

