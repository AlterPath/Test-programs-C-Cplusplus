pkg load communications;
symbols = [1 2 3 4 5 6 7 8];
probabilities = [1/2 1/4 1/8 1/16 1/32 1/64 1/128 1/128];
num_symbols = 1000;
SNR_dB = -5:1:5;
data = randsrc(1, num_symbols, [symbols; probabilities]);
timeline = []

for i = 1:length(SNR_dB)
  tic()
  summ = 0;

  # Кодер сигнала Шеннона-Фано
  encode_signal_dict = shannonfanodict(data, probabilities);
  encode_signal = shannonfanoenco(data, encode_signal_dict);
  # Кодер канала Хамминга
  encode_channel = (encode(encode_signal, 7, 4, "cyclic"))';
  # Модуляция
  modulated_data = pskmod(encode_channel,2);
  # Наложение шума
  received_data = awgn(modulated_data, SNR_dB(i));
  pause(0.01)
  # Демодуляция
  demodulated_data = pskdemod(received_data, 2);
  # Декодер канала Хамминга
  [MSG,ERR,CCODE,CERR] = decode(demodulated_data', 7, 4, "cyclic");
  decode_channel = (MSG)';
  # Декодер сигнала Шеннона-Фано
  decode_data = shannonfanodeco(decode_channel, encode_signal_dict);

  # Считаем ошибки и вероятность появления ошибки
  for j = 1:1:(num_symbols)
    if j > length(decode_data)
      summ = summ + 1;
    else
      if data(1,j) != decode_data(1,j)
        summ = summ + 1;
      endif
    endif
  end
  timeline(1,i) = toc()
end

figure 1
plot(SNR_dB, timeline);
title('Без переотправки')
xlabel('Шум, Дб')
ylabel('Время, с')


for i = 1:length(SNR_dB)
  err_arr = [];
  resend_data = data;
  saved_data = [];
  summ = 999999;

  tic()
  while summ != 0
    summ = 0;
    # Кодер сигнала Шеннона-Фано
    encode_signal_dict = shannonfanodict (resend_data, probabilities);
    encode_signal = shannonfanoenco(resend_data, encode_signal_dict);
    # Кодер канала Хамминга
    encode_channel = (encode(encode_signal, 7, 4, "cyclic"))';
    # Наложение шума
    received_data = round(awgn(encode_channel, SNR_dB(i)));
    for j = 1:1:length(received_data)
      if received_data(1,j) < 0
        received_data(1,j) = 0;
      endif
      if received_data(1,j) > 1
        received_data(1,j) = 1;
      endif
    endfor
    pause(0.01)
    # Декодер канала Хамминга
    [MSG,ERR,CCODE,CERR] = decode(received_data', 7, 4, "cyclic");
    decode_channel = (MSG)';
    # Декодер сигнала Шеннона-Фано
    decode_data = shannonfanodeco(decode_channel, encode_signal_dict);

    # Слияние декотированных данных с разных шагов цикла
    if length(err_arr) != 0
      for g = 1:1:length(err_arr)
        if g > length(decode_data)
          continue
        else
          saved_data(1,err_arr(g)) = decode_data(1,g);
        endif
      end
    else
      saved_data = decode_data;
    endif

    err_arr = [];

    # Считаем ошибки и вероятность появления ошибки
    for j = 1:1:(num_symbols)
      if j > length(saved_data)
        summ = summ + 1;
        err_arr = [err_arr; j];
      else
        if data(1,j) != saved_data(1,j)
          summ = summ + 1;
          err_arr = [err_arr; j];
        endif
      endif
    end

    # Переотправка данных в случае возникновения ошибок
    if length(err_arr) != 0
      for g = 1:1:length(err_arr)
        resend_data(1,g) = data(1,err_arr(g));
      end
    endif
  end

  printf('\nПри шуме в %dДб\n', SNR_dB(1,i))
  disp('Время:')
  timeline(1,i) = toc()
end

disp(timeline(1,i))

figure 2
plot(SNR_dB, timeline);
title('Без защитой с переотправкой')
xlabel('Шум, Дб')
ylabel('Время, с')


for i = 1:length(SNR_dB)
  err_arr = [];
  resend_data = data;
  saved_data = [];
  summ = 999999;

  tic()
  while summ != 0
    summ = 0;
    # Кодер сигнала Шеннона-Фано
    encode_signal_dict = shannonfanodict(resend_data, probabilities);
    encode_signal = shannonfanoenco(resend_data, encode_signal_dict);
    # Кодер канала Хамминга
    encode_channel = (encode(encode_signal, 7, 4, "cyclic"))';
    # Модуляция
    modulated_data = pskmod(encode_channel,2);
    # Наложение шума
    received_data = awgn(modulated_data, SNR_dB(i));
    pause(0.01)
    # Демодуляция
    demodulated_data = pskdemod(received_data, 2);
    # Декодер канала Хамминга
    [MSG,ERR,CCODE,CERR] = decode(demodulated_data', 7, 4, "cyclic");
    decode_channel = (MSG)';
    # Декодер сигнала Шеннона-Фано
    decode_data = shannonfanodeco(decode_channel, encode_signal_dict);

    # Слияние декотированных данных с разных шагов цикла
    if length(err_arr) != 0
      for g = 1:1:length(err_arr)
        if g > length(decode_data)
          continue
        else
          saved_data(1,err_arr(g)) = decode_data(1,g);
        endif
      end
    else
      saved_data = decode_data;
    endif

    err_arr = [];

    # Считаем ошибки и вероятность появления ошибки
    for j = 1:1:(num_symbols)
      if j > length(saved_data)
        summ = summ + 1;
        err_arr = [err_arr; j];
      else
        if data(1,j) != saved_data(1,j)
          summ = summ + 1;
          err_arr = [err_arr; j];
        endif
      endif
    end

    # Переотправка данных в случае возникновения ошибок
    if length(err_arr) != 0
      for g = 1:1:length(err_arr)
        resend_data(1,g) = data(1,err_arr(g));
      end
    endif
  end

  printf('\nПри шуме в %dДб\n', SNR_dB(1,i))
  disp('Время:')
  timeline(1,i) = toc()
end

disp(timeline(1,i))

# Расчет Tmin и Tmax для СЖРВ
Tmin = min(timeline)
Tmax = max(timeline)

# Расчет среднего граничного значения времени для СМРВ
Tlim = (Tmin + Tmax)/2

counter = 0
for i = 1:1:length(timeline)
  if timeline(i) > Tlim
    counter = counter + 1
  endif
end

# Расчет вероятности превышения граничного значения времени для СМРВ
Veroyatnost = counter/length(timeline)

figure 3
plot(SNR_dB, timeline);
title('С защитой и переотправкой')
xlabel('Шум, Дб')
ylabel('Время, с')
