MOV A, #30       ; Load 30 into A (the number to multiply)
MOV R1, A        ; Move A (30) to R1
MOV R0, #30      ; Initialize R0 to 30 for the loop counter

GO:
    MOV B, R1    ; Copy R1 to B
    MUL AB       ; Multiply A (in A) and B (in B), result in A (low byte), B (high byte)
    INC R1       ; Increment R1
    DJNZ R0, GO  ; Decrement R0, loop if not zero

MOV 40H, A       ; Store the lower byte (result) in memory location 40H
MOV 41H, B       ; Store the higher byte (result) in memory location 41H

END              ; Mark the end of the program
