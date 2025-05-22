; ******************************************************
; BASIC .ASM template file for AVR
; ******************************************************

.include "C:\VMLAB\include\m8def.inc"

; Define here the variables
;
.def  temp  =r16

; Define here Reset and interrupt vectors, if any
;
reset:
   rjmp start
   reti      ; Addr $01
   reti      ; Addr $02
   reti      ; Addr $03
   reti      ; Addr $04
   reti      ; Addr $05
   reti      ; Addr $06        Use 'rjmp myVector'
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
   ldi r20, 0x34      ; XL
    ldi r21, 0x12      ; XH

    ldi r22, 0xC8      ; YL
    ldi r23, 0x00      ; YH

    mul r20, r22       ; R1:R0 = XL * YL
    mov r16, r0        ;
    mov r17, r1        ; Следующий байт

    mul r20, r23       ; R1:R0 = XL * YH
    add r17, r0        ; Складываем со сдвигом
    adc r18, r1

    mul r21, r22       ; R1:R0 = XH * YL
    add r17, r0
    adc r18, r1

    mul r21, r23       ; R1:R0 = XH * YH
    add r19, r0
    adc r19, r1        ; только R0 тут интересен

    ;Результат в R19:R18:R17:R16

forever:
   nop
   nop       ; Infinite loop.
   nop       ; Define your main system
   nop       ; behaviour here
rjmp forever

; X = 0x1234 ; Y = 0x00C8

