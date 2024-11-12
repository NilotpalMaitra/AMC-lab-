MOV TMOD, #01h  ; Set Timer 0 to Mode 1 (16-bit mode)
    
    ; Calculate the delay for half of the triangular wave period (250 µs).
    ; Timer clock frequency is assumed to be 12 MHz. Timer overflow happens every 1.085 µs.
    ; For 250 µs delay, we need to calculate the timer values.
    
    MOV TH0, #0x3C  ; Load high byte of Timer 0 (calculated for ~250 µs delay)
    MOV TL0, #0xAF  ; Load low byte of Timer 0 (calculated for ~250 µs delay)
    
    SETB TR0        ; Start Timer 0

MAIN_LOOP:
    ; Rising edge of triangular wave (P1.0 goes high)
    SETB P1.0       ; Set P1.0 high (rise)
    CALL DELAY      ; Wait for 250 µs
    
    ; Falling edge of triangular wave (P1.0 goes low)
    CLR P1.0        ; Set P1.0 low (fall)
    CALL DELAY      ; Wait for 250 µs
    
    SJMP MAIN_LOOP  ; Infinite loop to continuously generate the triangular wave

DELAY:
    ; Wait for Timer 0 overflow (each overflow gives ~1.085 µs delay)
    JNB TF0, $      ; Wait for the Timer 0 overflow flag
    CLR TF0         ; Clear the Timer 0 overflow flag
    RET             ; Return from delay function

END
