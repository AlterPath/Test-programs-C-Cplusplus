pkg load communications

symbols = [1 2 3 4 5 6 7 8];
probabilities = [0.5 0.25 0.15 0.1 0.04 0.03 0.02 0.01];
probabilities = probabilities / sum(probabilities);
shannonfanotable = shannonfanodict(symbols, probabilities)
input_s = randsrc(1, 1000, [symbols; probabilities]);
encoded_s = shannonfanoenco(input_s, shannonfanotable)
[H, G, N, K] = hammgen(3);
code = encode(encoded_s, N, K, "hamming");
sig = (code * 2 - 1) + 1i * 0;
SNR = -5:1:5;
mult = 10 .^ (SNR / 20);
BER = zeros(1, length(SNR));
code_noised = [];
noise = (randn(1, 1) + 1i * randn(1, 1)) / sqrt(2);
mix = mult(N) * sig(K) + noise;
spec = fft(mix);
phase = abs(angle(spec));
if (phase > pi / 2)
	code_noised(K) = 0;
elseif (phase < pi / 2)
	code_noised(K) = 1;
endif
[msg, err, ccode, cerr] = decode(code_noised', N, K, "hamming");
decoded_s = shannonfanodeco(msg, hd);
for m = 1:length(input_s)
		if input_s(m) != decoded_s(m)
			BER(n) = BER(n) + 1;
		endif
end
semilogy(SNR, (BER ./ length(sig))); grid on;
ylabel('BER'); xlabel('SNR, dB');


