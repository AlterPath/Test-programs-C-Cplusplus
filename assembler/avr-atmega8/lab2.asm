; ******************************************************
; BASIC .ASM template file for AVR
; ******************************************************

.include "C:\VMLAB\include\m8def.inc"

; Define here the variables
;
.def  temp  =r16
.def led_state = r17

.org 0x0000
    rjmp reset
.org INT0addr
    rjmp int0_handler

reset:
    ; Настройка стека
    ldi temp, LOW(RAMEND)
    out SPL, temp
    ldi temp, HIGH(RAMEND)
    out SPH, temp

    ; Настраиваем PB0 как выход (для светодиода)
    sbi DDRB, PB0

    ; Светодиод изначально выключен (на PB0 — лог.1)
    sbi PORTB, PB0

    ; Настроим PD2  (INT0) как вход
    cbi DDRD, PD2

    ; Включим встроенную подтяжку
    sbi PORTD, PD2

    ; Настраиваем прерывание INT0 по спаду
    ldi temp, (1 << ISC01)    ; ISC01=1, ISC00=0 → спад
    out MCUCR, temp

    ; Разрешаем внешнее прерывание INT0
    ldi temp, (1 << INT0)
    out GICR, temp

    ; Включаем глобальные прерывания
    sei

main_loop:
    rjmp main_loop

; --- Обработчик прерывания ---
int0_handler:
    ; Задержка ~30 мс для подавления дребезга
    rcall delay_ms_30

    ; Проверяем: PD2 всё ещё в лог.0?
    sbis PIND, PD2     ; если PD2=1 — пропускаем
    rjmp toggle_led

    reti               ; иначе — выходим

toggle_led:
    ; Читаем текущее состояние PB0
    in temp, PINB
    sbrs temp, PB0     ; если 1 → пропускаем
    rjmp led_on
    rjmp led_off

led_on:
    cbi PORTB, PB0     ; лог.0 — включаем
    rjmp end_int

led_off:
    sbi PORTB, PB0     ; лог.1 — выключаем

end_int:
    reti

; --- Задержка ~30 мс ---
delay_ms_30:
    ; Задержка 30 мс (прибл. при 1 МГц)
    ; 1 такт = 1 мкс → нужно 30 000 тактов
    ldi r18, 120
outer:
    ldi r19, 250
inner:
    nop
    dec r19
    brne inner
    dec r18
    brne outer
    ret

start:
   nop       ; Initialize here ports, stack pointer,
   nop       ; cleanup RAM, etc.
   nop       ;
   nop       ;

forever:
   nop
   nop       ; Infinite loop.
   nop       ; Define your main system
   nop       ; behaviour here
rjmp forever

