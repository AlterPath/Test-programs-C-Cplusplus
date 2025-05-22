; ******************************************************
; BASIC .ASM template file for AVR
; ******************************************************

.include "C:\VMLAB\include\m8def.inc"

; Define here the variables
;
.def  temp  =r16
.equ one =0b11111001
.equ two   = 0b10100100
.equ three = 0b10110000
.equ four  = 0b10011001
.equ five  = 0b10010010
.equ six   = 0b10000010
.equ seven = 0b11111000
.equ eight = 0b10000000
.equ nine  = 0b10010000
.equ zero  = 0b11000000


; Define here Reset and interrupt vectors, if any
;
reset:
   rjmp start
   reti      ; Addr $01
   reti      ; Addr $02
   reti      ; Addr $03
   reti      ; Addr $04
   reti      ; Addr $05
   rjmp timer      ; Addr $06        Use 'rjmp myVector'
   reti      ; Addr $07        to define a interrupt vector
   reti      ; Addr $08
   reti      ; Addr $09
   reti      ; Addr $0A
   reti      ; Addr $0B        This is just an example
   reti      ; Addr $0C        Not all MCUs have the same
   reti      ; Addr $0D        number of interrupt vectors
   reti      ; Addr $0E
   reti      ; Addr $0F
   reti      ; Addr $10

; Program starts here after Reset
;
start:
  ldi r16, high(RAMEND) ; Загружаем старший байт адреса конца ОЗУ в r16
  out SPH, r16
  ldi r16, low(RAMEND) ; Загружаем младший байт адреса конца ОЗУ
  out SPL, r16
  ldi r16, 0xFF
  out ddrb, r16 ; Устанавливаем все порта B как выходы
  out ddrd, r16
  clr r17
  ldi r16, (1<<ISC01) ; Прерывающий вход на спад
  out MCUCR, r16 ; MCU Control Register - управляет режимами внешнего прерывания
  ldi r16, (1<<INT0) ; Разрешаем внешнее прерывание INT0
  out GICR, r16 ; General Interrupt Control Register
  ldi r16, high(19531)
  out OCR1AH, r16 ; регистры сравнения таймера 1 (Output Compare A High/Low).
  ldi r16, low(19531)
  out OCR1AL, r16
  ldi r16, (1<<TICIE1)|(1<<OCIE1A)
  out TIMSK, r16
  ldi r16, (1<<WGM12)|(1<<CS12)
  out TCCR1B, temp ; Включаем режим сравнения
  sei ; ФЛАГ ГЛОБАЛЬНЫХ ПРЕРЫВАНИЙ

  ldi r31, 0b11111110
  out portd, r31
  ldi r18, seven
  out portb, r18
forever:
	
	rjmp forever




  ror r31 ; Циклический сдвиг вправо значения в r31. Бит двигается по порту D
  out portb, r17
  out portd, r31
  ldi r18, zero
  out portb, r18

  ror r31
  out portb, r17
  out portd, r31
  ldi r18, three
  out portb, r18

  ror r31
  out portb, r17
  out portd, r31
  ldi r18, one
  out portb, r18

rjmp forever

wait:
  set
  reti

timer:
	cpi r31, 0xFE
	BRNE pc+3
   ldi r18, seven
   out portb, r18
   cpi r31, 0xFD
	BRNE pc+3
   ldi r18, zero
   out portb, r18
   cpi r31, 0xFB
	BRNE pc+3
   ldi r18, three
   out portb, r18
   cpi r31, 0xF7
	BRSH pc+6
   ldi r18, one
   out portb, r18
   ldi r31, 0b11111110
   out portd, r31
   reti
   lsl r31
	inc r31
	out portd, r31
	reti
