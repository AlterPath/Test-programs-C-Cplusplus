% --- Код Хэмминга (15, 11) ---
r = 4;
[H,G,n,k] = hammgen(r);

disp("Порождающая матрица G (15,11):")
disp(G)

disp("Проверочная матрица H (15,11):")
disp(H)

% --- Кодирование информационного вектора ---
info_vector = [1 0 1 1 1 1 0 1 0 1 1];
codeword = encode(info_vector, n, k, 'hamming');

disp("Закодированный вектор:")
disp(codeword)

% --- Десятичное представление ---
decimal_value = bi2de(info_vector);

disp("Десятичное представление информационного вектора:")
disp(decimal_value)

% --- Кодирование в десятичном режиме ---
decimal_codeword = encode(decimal_value, n, k, 'hamming/decimal');

disp("Закодированный вектор в десятичном режиме:")
disp(decimal_codeword)

% --- Внесение ошибки и декодирование ---
err_pos = 10;
codeword_with_error = codeword;
codeword_with_error(err_pos) = ~codeword_with_error(err_pos);

decoded_vector = decode(codeword_with_error, n, k, 'hamming');

disp("Декодированный вектор:")
disp(decoded_vector)


% --- Коды Хэмминга для сравнения методом Монте-Карло ---
r1 = 4;
r2 = 6;
[H1,G1,n1,k1] = hammgen(r1);
[H2,G2,n2,k2] = hammgen(r2);

p = [5e-4 1e-3 5e-3 1e-2 5e-2 1e-1];
stat = zeros(4, 6);

for i = 1:6
    % --- Код Хэмминга (15, 11) ---
    msg1 = randi([0 1], 1e5, k1);
    menc1 = encode(msg1, n1, k1, 'hamming');
    mrec1 = bsc(menc1, p(i));
    mdec1 = decode(mrec1, n1, k1, 'hamming');
    [~, stat(1,i)] = biterr(msg1, mdec1);

    % --- Код Хэмминга (63, 57) ---
    msg2 = randi([0 1], 1e5, k2);
    menc2 = encode(msg2, n2, k2, 'hamming');
    mrec2 = bsc(menc2, p(i));
    mdec2 = decode(mrec2, n2, k2, 'hamming');
    [~, stat(2,i)] = biterr(msg2, mdec2);

    % --- Без кодирования ---
    mrec3 = bsc(msg1, p(i));
    [~, stat(3,i)] = biterr(msg1, mrec3);
end

% --- Построение графика ---
figure;
loglog(p, stat(1,:), 'r', 'LineWidth', 2);
hold on;
loglog(p, stat(2,:), 'b', 'LineWidth', 2);
loglog(p, stat(3,:), 'k', 'LineWidth', 2);
hold off;

title('Сравнение кодов Хэмминга (15,11), (63,57) и без кодирования');
xlabel('Вероятность ошибки в BSC канале');
ylabel('BER после декодирования');
legend('Хэмминг (15,11)', 'Хэмминг (63,57)', 'Без кодирования', 'Location', 'northwest');
grid on;

