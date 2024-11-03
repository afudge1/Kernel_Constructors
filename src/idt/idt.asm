section .text

extern interrupt_handler

global idt_load
global interrupt_pointer_table
global outb
global insb

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8]
    lidt [ebx]

    pop ebp
    ret

%macro interrupt 1 
    global int%1
    int%1:
        ; INTERRUPT FRAME START
        ; ALREADY PUSHED TO US BY THE PROCESSOR UPON ENTRY TO THIS INTERRUPT
        ; uint32_t ip
        ; uint32_t cs;
        ; uint32_t flags;
        ; uint32_t sp;
        ; uint32_t ss;
        ; Pushes the general purpose registers to the stack
        pushad
        ; Interrupt frame end
        ; //Push the stack pointer so that we are pointing to the interrupt frame
        push esp
        push dword %1
        call interrupt_handler
        add esp, 8
        popad
        iret
%endmacro

%macro interrupt_array_entry 1
    dd int%1
%endmacro

%assign i 0
%rep 512
    interrupt i
    %assign i i+1
%endrep

interrupt_pointer_table:
    %assign i 0
    %rep 512
        interrupt_array_entry i
        %assign i i+1
    %endrep

outb:
    push ebp
    mov ebp, esp

    mov eax, [ebp+12]
    mov edx, [ebp+8]
    out dx, al

    pop ebp
    ret

outw:
    push ebp
    mov ebp, ebp

    mov eax, [ebp+12]
    mov edx, [ebp+8]
    out dx, ax

    pop ebp
    ret