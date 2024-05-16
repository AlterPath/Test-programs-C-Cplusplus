%{
clc;
pkg load communications;
N = 5;
p = (40-N)/100;     % Вероятность ошибки в канале
L = [100, 500, 1e3, 5e3, 1e4, 5e4, 1e5];  % Размер массива данных
stat = zeros(7, length(L)); % Статистика

for i = 1:length(L)
  d = randint(1, L(i));

  % 5 экспериментов
  for j = 1:5
    [a, stat(j, i)] = biterr(d, bsc(d, p));
  endfor

  % Вычисление среднего и СКО
  stat(6, i) = mean(stat(1:5, i));
  stat(7, i) = std(stat(1:5, i));
endfor



% Построение графиков
semilogx(L, stat(1:5, :), 'b', L, stat(6, :), 'r', L, stat(7, :), 'g');
grid on;
xlim([L(1), L(end)]);

% Добавление названия графика
title("Octave BSC");

% Добавление подписей осей
xlabel("Data Size (L)");
ylabel("Bit Error Rate");

% Добавление легенды
legend("Experiment 1", "Experiment 2", "Experiment 3", "Experiment 4", "Experiment 5", "Mean", "Standard Deviation");
%}

p = [11e-4, 5e-4, 1e-3, 5e-3, 1e-2, 5e-2, 1e-1];

function OUT = MyBSC(IN, P)
  OUT = xor(IN, rand(size(IN)) <= P);
endfunction

statBSC = zeros(6, length(p));
statMyBSC = zeros(6, length(p));

d = randi([1, 2], 1, 105) - 1;

for i = 1:length(p)
  for j = 1:5
    [~, statBSC(j, i)] = biterr(d, bsc(d, p(i)));
    [~, statMyBSC(j, i)] = biterr(d, MyBSC(d, p(i)));
  endfor
  statBSC(6, i) = mean(statBSC(1:5, i));
  statMyBSC(6, i) = mean(statMyBSC(1:5, i));
endfor

subplot (1, 2, 1);
loglog(p(:), statBSC(1:5, :), 'b:', p, statBSC(6, :), 'r-');
grid on;
title("Octave BSC");

subplot (1, 2, 2);
loglog(p(:), statMyBSC(1:5, :), 'b:', p, statMyBSC (6, :), 'r-');
grid on;
title("My BSC");
sgtitle ('Сравнение BSC');
