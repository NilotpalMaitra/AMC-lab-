 mov ax, @data
    mov ds, ax

    ; Display prompt
    lea dx, prompt                    ; Load address of prompt string
    mov ah, 09h                        ; DOS interrupt to display string
    int 21h

    ; Input x value
    mov ah, 01h                        ; DOS interrupt to read single character input
    int 21h
    sub al, '0'                        ; Convert ASCII to integer
    mov bl, al                         ; Store input in BL register (x)

    ; Calculate x² (x * x)
    mov al, bl                         ; Load x (stored in BL) into AL
    mul bl                              ; AX = AL * BL => x² in AX

    ; Multiply 6 * x² (6x²)
    mov cx, 6                          ; Load 6 into CX
    mul cx                              ; AX = AX * 6 => 6x² in AX

    ; Store result of 6x² in DX
    mov dx, ax                          ; Move 6x² result to DX

    ; Calculate -9x (multiply x by -9)
    mov al, bl                         ; Load x (stored in BL) into AL
    mov cx, 9                          ; Load 9 into CX
    mul cx                              ; AX = AL * CX => x * 9 in AX
    neg ax                              ; Negate the result to get -9x

    ; Add -9x to 6x²
    add dx, ax                          ; DX = 6x² + (-9x)

    ; Add 2 (constant term) to result
    add dx, 2                           ; DX = 6x² - 9x + 2

    ; Display the result
    lea dx, result                      ; Load address of result string
    mov ah, 09h                         ; DOS interrupt to display string
    int 21h

    ; Print the result (in DX register, as a 16-bit number)
    mov ax, dx                          ; Move result to AX
    call PrintNum                
