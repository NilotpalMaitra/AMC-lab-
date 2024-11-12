 MOV TMOD, #01h  ; Set Timer 0 to Mode 1 (16-bit mode)
    MOV TH0, #0x3C  ; Load high byte for 1000 ms delay (adjust as per desired frequency)
    MOV TL0, #0xB0  ; Load low byte for 1000 ms delay (adjust as per desired frequency)
    
    SETB TR0        ; Start Timer 0

MAIN_LOOP:
    ; Generate high part of the square wave (60% duty cycle)
    SETB P1.0       ; Set P1.0 high
    CALL DELAY      ; Delay for high time (60% of period)
    
    ; Generate low part of the square wave (40% duty cycle)
    CLR P1.0        ; Set P1.0 low
    CALL DELAY      ; Delay for low time (40% of period)

    SJMP MAIN_LOOP  ; Infinite loop to continuously generate the square wave

DELAY:
    MOV R0, #10     ; Set R0 to 10 iterations of Timer
DELAY_LOOP:
    JNB TF0, $      ; Wait for Timer 0 overflow (delay completion)
    CLR TF0         ; Clear Timer 0 overflow flag
    NOP             ; No operation, just wait for the next cycle
    DJNZ R0, DELAY_LOOP  ; Decrement R0 and repeat if it's not zero
    RET             ; Return from delay function

END
