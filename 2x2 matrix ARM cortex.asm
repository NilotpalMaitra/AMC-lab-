LDR     R0, =matrix_A  // R0 = address of matrix_A
    LDR     R1, =matrix_B  // R1 = address of matrix_B
    LDR     R2, =matrix_C  // R2 = address of matrix_C

    // Load elements of Matrix A into registers
    LDR     R3, [R0]      // R3 = a11
    LDR     R4, [R0, #4]  // R4 = a12
    LDR     R5, [R0, #8]  // R5 = a21
    LDR     R6, [R0, #12] // R6 = a22

    // Load elements of Matrix B into registers
    LDR     R7, [R1]      // R7 = b11
    LDR     R8, [R1, #4]  // R8 = b12
    LDR     R9, [R1, #8]  // R9 = b21
    LDR     R10, [R1, #12] // R10 = b22

    // Compute c11 = a11 * b11 + a12 * b21
    MUL     R11, R3, R7   // R11 = a11 * b11
    MUL     R12, R4, R9   // R12 = a12 * b21
    ADD     R11, R11, R12 // R11 = c11

    // Store c11 in matrix C
    STR     R11, [R2]     // matrix_C[0] = c11

    // Compute c12 = a11 * b12 + a12 * b22
    MUL     R11, R3, R8   // R11 = a11 * b12
    MUL     R12, R4, R10  // R12 = a12 * b22
    ADD     R11, R11, R12 // R11 = c12

    // Store c12 in matrix C
    STR     R11, [R2, #4] // matrix_C[1] = c12

    // Compute c21 = a21 * b11 + a22 * b21
    MUL     R11, R5, R7   // R11 = a21 * b11
    MUL     R12, R6, R9   // R12 = a22 * b21
    ADD     R11, R11, R12 // R11 = c21

    // Store c21 in matrix C
    STR     R11, [R2, #8] // matrix_C[2] = c21

    // Compute c22 = a21 * b12 + a22 * b22
    MUL     R11, R5, R8   // R11 = a21 * b12
    MUL     R12, R6, R10  // R12 = a22 * b22
    ADD     R11, R11, R12 // R11 = c22

    // Store c22 in matrix C
    STR     R11, [R2, #12] // matrix_C[3] = c22

    // End of program (in embedded systems, you may want to loop indefinitely here)
end:
    B       end             // Infinite loop to end the program
