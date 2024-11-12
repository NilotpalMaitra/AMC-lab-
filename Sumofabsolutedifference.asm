MOV R0, #0               ; R0 will store the sum of absolute differences, initialize to 0
    LDR R1, =A               ; R1 points to the start of Array A
    LDR R2, =B               ; R2 points to the start of Array B
    LDR R3, =n               ; R3 stores the array length (n = 8)

loop:
    LDR R4, [R1], #4         ; Load element A[i] into R4, increment R1 by 4 (size of 1 word)
    LDR R5, [R2], #4         ; Load element B[i] into R5, increment R2 by 4 (size of 1 word)

    ; Calculate the absolute difference |A[i] - B[i]|
    SUB R6, R4, R5           ; R6 = A[i] - B[i]
    CMP R6, #0               ; Compare (A[i] - B[i]) with 0
    BGE no_neg               ; If A[i] >= B[i], skip negation
    NEG R6, R6               ; R6 = -(A[i] - B[i]) (convert negative to positive)

no_neg:
    ADD R0, R0, R6           ; Add the absolute difference to the sum in R0

    SUBS R3, R3, #1          ; Decrement the loop counter (n-1)
    BNE loop                 ; If the counter is not zero, repeat the loop

    ; Store the result in memory or return it
    LDR R7, =result          ; Load the address of the result
    STR R0, [R7]             ; Store the result (sum of absolute differences) in memory

    ; End of program (infinite loop for stopping)
    B .   
