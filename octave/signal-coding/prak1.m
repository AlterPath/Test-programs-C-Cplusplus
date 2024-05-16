a = -1.5;
b = -0.5;
c = 2;
d = 3;
l = 2;
N = 256;
T = 2 * l;
df=1/T;
Nyq=N/(2*T);
t = linspace(0, T, N);
s = zeros(1, N);

for i = 1:N
    x = rem(t(i), T) - l; % Приводим x к интервалу [-l, l)
    if x >= -l && x < 0
        s(i) = a * x + b;
    elseif x >= 0 && x <= l
        s(i) = c * x + d;
    end
end

F = fft(s) / N;
subplot(311);
plot(t, s);
title('Сигнал f(x)');
xlabel('Время');
ylabel('Амплитуда');
F1=F(1:N/2+1);
F2=F(N/2+1:N);
F=[F2,F1];

subplot(312);
nu=-Nyq+df*(0:N);
plot(nu(1:N),abs(F(1:N)));

xlabel("Частота");
ylabel('Амплитуда');

subplot(313);
plot(nu(1:N),angle(F(1:N)));
xlabel("Частота");
ylabel('Фаза');

