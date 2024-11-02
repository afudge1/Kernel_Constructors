ORG 0x0100000
[BITS 32]

    ; Enable the A20 line
    in al, 0x92
    or al, 2
    out 0x92, al
    
    ; cpuid for longmode detection
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .noLongMode

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .noLongMode




    
.noLongMode:
    jmp $