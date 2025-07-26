; echo in x86-64 Linux 
; AUTHOR : mateo-rfz

section .data 
    space db " "
    nw db 0ah ; new line

    help_msg db "Usage: echo [STRING...]" , 0ah


section .text 
    global _start 


_start : 
    mov r8 , [rsp] ; r8 -> argc (arg counter)
    cmp r8 , 1 
    je help

    mov r9 , rsp 
    lea r9 , [r9 + 16] ; 8 for argc , 8 for program name
    
    dec r8 ; skip program name in counter

    .loop : ; main loop 
        call write

        cmp r8 , 1
        je exit 

        lea r9 , [r9 + 8]
        dec r8 
        jmp .loop
        




    write : 
        xor rdx , rdx ; counter 
        mov rsi , [r9]

        .length : 
            mov al , [rsi + rdx]
            cmp al , 0 
            je show_output 
            inc rdx 
            jmp .length

        
        show_output : 
            mov rax , 1 
            mov rdi , 1 
            mov rsi , [r9]
            syscall 


            cmp r8 , 1 
            je new_line 

            mov rax , 1 
            mov rdi , 1 
            mov rsi , space
            mov rdx , 1 
            syscall 
        
        ret 


    new_line : 
        mov rax , 1 
        mov rdi , 1 
        mov rsi , nw
        mov rdx , 1 
        syscall 

        jmp exit 
        


    exit : 
        mov rax , 60
        xor rdi , rdi 
        syscall



    help : 
        mov rax , 1
        mov rdi , 1 
        mov rsi , help_msg 
        mov rdx , 47 
        syscall 

        jmp exit
        
