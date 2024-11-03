[BITS 32]
_start:
    extern kmain
    call kmain
    jmp $