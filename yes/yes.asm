; yes in x86-64 linux
; AUTHOR : mateo-rfz


section .data 
    y db "y" , 0ah 
    nw db 0ah 



section .text 
    global _start 



_start : 
    mov rax , [rsp] ; move argc to rax 
    cmp rax , 1
    je write
    jmp ewrite







    ewrite :
        lea r9 , [rsp + 16] ; skip argc and program name 
        
        xor r10 , r10
        mov rsi , [r9]
        mov r12 , rsi

        .length : 
            mov al , [rsi + r10]
            cmp al , 0 
            je .loop 
            inc r10 
            jmp .length

        .loop : 
            mov rax , 1
            mov rdi , 1 
            mov rsi , r12
            mov rdx , r10
            syscall 

            mov rax , 1 
            mov rdi , 1
            mov rsi , nw
            mov rdx , 1  
            syscall 

            jmp .loop








    write :
        .loop : 
            mov rax , 1 
            mov rdi , 1 
            mov rsi , y
            mov rdx , 2
            syscall
            jmp .loop

