ORG 0x7c00
[BITS 16]

_start:
    jmp short start
        nop

; Add filesystem here

start:
    ; for old bioses that might load the bootloader into 0x7c00:0x0 instead of 0x0:0x7c00
    jmp 0x0:biosthing
biosthing:
    ; set segment registers
    cli
    mov ax, 0x0
    mov ds, ax
    mov es, ax
    mov ss, ax
    ; set stack to 0x7c00
    mov sp, 0x7c00
loadProtectedMode:
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp protectedMode

; GDT
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

; offset 0x8
gdt_code:       ; CS SHOULD POINT TO THIS
    dw 0xffff   ; Segment limit first 0-15 bits
    dw 0        ; Base first 0-15 bits
    db 0        ; Base 16-23 bytes
    db 0x9a     ; Access byte
    db 11001111b ; High 4 bit flags and the low 4 bit flags
    db 0        ; Base 24-31 bits

; offset 0x10
gdt_data:        ; DS, SS, ES, FS, GS
    dw 0xffff   ; Segment limit first 0-15 bits
    dw 0        ; Base first 0-15 bits
    db 0        ; Base 16-23 bytes
    db 0x92     ; Access byte
    db 11001111b ; High 4 bit flags and the low 4 bit flags
    db 0        ; Base 24-31 bits

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start-1
    dd gdt_start

[BITS 32]
protectedMode:
    mov eax, 1
    mov ecx, 100
    mov edi, 0x0100000
    call ata_lba_driver
    jmp 0x0100000

ata_lba_driver:
    ; Send the highest 8 bits of the LBA to the hard disk controller
    shr eax, 24              ; Shift right to get the highest 8 bits of LBA in AL
    or eax, 0xE0             ; Set master drive bit (0xE0) with the highest LBA bits
    mov dx, 0x1F6            ; Select the drive/head register
    out dx, al               ; Output the register value to 0x1F6

    mov eax, ecx             ; Move the sector count into EAX
    mov dx, 0x1F2            ; Sector count register
    out dx, al               ; Output the sector count to 0x1F2

    ; Send the lowest 8 bits of the LBA
    mov eax, ebx             ; Restore the full LBA from EBX
    mov dx, 0x1F3            ; Low byte of LBA register
    out dx, al               ; Output LBA[0:7]

    ; Send bits 8–15 of the LBA
    mov dx, 0x1F4
    mov eax, ebx
    shr eax, 8               ; Shift right to get LBA[8:15] in AL
    out dx, al               ; Output LBA[8:15]

    ; Send bits 16–23 of the LBA
    mov dx, 0x1F5
    mov eax, ebx
    shr eax, 16              ; Shift right to get LBA[16:23] in AL
    out dx, al               ; Output LBA[16:23]

    ; issue read command
    mov dx, 0x1F7            ; Command register
    mov al, 0x20             ; ATA read command (0x20 for reading sectors)
    out dx, al               ; Send the read command

.next_sector:
    push ecx                 ; Preserve the remaining sector count on the stack

.try_again:
    mov dx, 0x1F7            ; Status register
    in al, dx                ; Read the status
    test al, 8               ; Check the Data Ready (DRQ) bit
    jz .try_again            ; Wait until the drive signals data is ready

    ; Read 256 words (512 bytes) per sector into memory
    mov ecx, 256             ; Each sector is 512 bytes, read in words (2 bytes each)
    mov dx, 0x1F0            ; Data register
    rep insw                 ; Read 256 words from data register into [ES:DI]

    pop ecx                  ; Restore the sector count
    loop .next_sector        ; Repeat until all sectors are read
    ; End of reading sectors into memory
    ret

times 510-($ - $$) db 0
dw 0xAA55