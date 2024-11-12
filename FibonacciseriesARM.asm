LDR     R0, =fib_count  // Load address of fib_count into R0
    LDR     R1, [R0]        // Load number of Fibonacci numbers (n) into R1
    
    // Initialize first two Fibonacci numbers F(0) = 0, F(1) = 1
    MOV     R2, #0          // F(0) = 0
    MOV     R3, #1          // F(1) = 1
    LDR     R4, =fib_series // Load base address of fib_series into R4
    STR     R2, [R4]        // Store F(0) in fib_series[0]
    STR     R3, [R4, #4]    // Store F(1) in fib_series[1]
    
    // Loop to compute Fibonacci numbers
    MOV     R5, #2          // Start with index 2 (F(2))

fibonacci_loop:
    CMP     R5, R1          // Compare current index (R5) with the total number of terms (R1)
    BGE     done            // If index >= n, exit loop

    // Calculate the next Fibonacci number
    ADD     R6, R2, R3      // R6 = F(n-1) + F(n-2)
    
    // Store the result in the fib_series array
    STR     R6, [R4, R5, LSL #2]  // Store Fibonacci number in fib_series[index]
    
    // Move values for the next iteration
    MOV     R2, R3          // F(n-2) = F(n-1)
    MOV     R3, R6          // F(n-1) = F(n)

    // Increment index (R5) for next Fibonacci number
    ADD     R5, R5, #1      // R5 = index + 1

    // Continue the loop
    B       fibonacci_loop

done:
    // Program done, loop indefinitely (or could return to a system state)
    B       done      
