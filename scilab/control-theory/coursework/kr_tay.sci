// Параметры варианта 7
k_н = 1.2;          // Коэффициент усиления
T = 0.2;             // Период дискретизации
a = exp(-0.04);      // e^(-T/T1) = e^(-0.4/5)

// Создание полиномиальной переменной
z = poly(0, 'z');

// Передаточная функция разомкнутой системы
W_razomk = k_н * ( -5 + 0.4/(z-1) + 5*(z-1)/(z - a) );

// Передаточная функция замкнутой системы
W_zamk = W_razomk / (1 + W_razomk);

// Проверка устойчивости
poles = roots(denom(W_zamk));
abs_poles = abs(poles);
disp("Модули корней: ", abs_poles);

// Временной вектор
t = 0:T:50;         // От 0 до 20 с шагом T

// Входные воздействия (0, 10, 20)
u_zero = zeros(t);   // x(t)=0
u_ten = 30*ones(t);  // x(t)=10
u_twenty = 50*ones(t); // x(t)=20

// Моделирование
y_zero = flts(u_zero, tf2ss(W_zamk));
y_ten = flts(u_ten, tf2ss(W_zamk));
y_twenty = flts(u_twenty, tf2ss(W_zamk));

// Построение графиков
scf(0);
plot(t, y_zero, 'r-', t, y_ten, 'b-', t, y_twenty, 'g-', 'LineWidth', 2);
xgrid();
legend(['x(t)=0', 'x(t)=30', 'x(t)=50'], 2);
xtitle('Переходные процессы', 'Время, с', 'Выход y(t)');
xs2png(gcf(), 'переходные_процессы.png');
// Анализ установившегося режима
for i=1:length(t)
    if t(i) > 15  // Анализ после 15 секунд
        disp("Для x(t)=10:");
        disp("Установившееся значение: " + string(mean(y_ten(i:$))));
        disp("Ошибка: " + string(10 - mean(y_ten(i:$))));
        
        disp("Для x(t)=20:");
        disp("Установившееся значение: " + string(mean(y_twenty(i:$))));
        disp("Ошибка: " + string(20 - mean(y_twenty(i:$))));
        break;
    end
end

// Расчет перерегулирования (для x(t)=10)
y_max = max(y_ten);
y_ust = mean(y_ten($-10:$));  // Последние 10 значений
sigma = 100*(y_max - y_ust)/y_ust;
disp("Перерегулирование: " + string(sigma) + "%");

// Исследование при k_н = 4.222
k_н_pred = 4.222;
W_razomk_pred = k_н_pred * ( -5 + 0.4/(z-1) + 5*(z-1)/(z - a) );
W_zamk_pred = W_razomk_pred / (1 + W_razomk_pred);

// Моделирование
y_pred = flts(u_ten, tf2ss(W_zamk_pred));

// Построение графика
scf(1);
plot(t, y_pred, 'm-', 'LineWidth', 2);
xgrid();
xtitle('Система на границе устойчивости (k_н=4.222)', 'Время, с', 'Выход y(t)');
xs2png(gcf(), 'граница_устойчивости.png');

// Проверка корней
poles_pred = roots(denom(W_zamk_pred));
abs_poles_pred = abs(poles_pred);
disp("Модули корней при k_н=4.222: ", abs_poles_pred);// Построение АЧХ
scf(2);
bode(W_zamk, 0.01, 100);
xs2png(gcf(), 'частотные_характеристики.png');
