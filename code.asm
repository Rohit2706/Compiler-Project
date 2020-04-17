SECTION .data
inputi  db "Input: Enter an integer value",00h
inputb  db "Input: Enter a boolean value",00h
output db "Output: ",00h
formatstring db "%s",00h
newline db 0Ah,00h
space db " ",00h
formatint db "%hi",00h
printint db "%hi ",00h
formatbool db "%hi",00h
true db "true ",00h
false db "false ",00h
range1 dw 0
range2 dw 0
base dq 0
formatarray db "Input: Enter %hi elements of %s type for range %hi to %hi ",00h 
INTEGER db "integer",00h
BOOLEAN db "boolean",00h
booltemp dw 0

SECTION .text
global main
extern printf
extern scanf

main:
   call driver

   mov rax, 60
   xor rdi, rdi
   syscall

driver:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    push rbp

    mov rdi, formatstring
    mov rsi, inputi
    xor rax, rax
    call printf

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

    mov rdi, formatint
    mov rsi, rbp
    sub rsi, 2
    mov rax, 0
    call scanf

    mov rax, 19
    push rax
    pop rax
    mov rbx, rbp
    sub rbx, 4
    mov word[rbx], ax

    mov rax, 56
    push rax
    pop rax
    mov rbx, rbp
    sub rbx, 6
    mov word[rbx], ax

switch1:
    mov ax, word[rbp - 2]
    push rax
    pop r10

.case1:
    mov rax, 1
    push rax
    pop rax
    cmp r10w, ax
    jne .case2
    mov ax, word[rbp - 2]
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 4]
    push rax
    pop rbx
    pop rax
    sub ax, bx
    push rax

    pop rax
    mov rbx, rbp
    sub rbx, 4
    mov word[rbx], ax

    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov rdi, printint
    xor rsi, rsi
    mov si, word[rbp-4]
    mov rax, 0
    call printf

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

    jmp .endswitch

.case2:
    mov rax, 2
    push rax
    pop rax
    cmp r10w, ax
    jne .case3
    mov ax, word[rbp - 2]
    push rax
    mov rax, 3
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 6]
    push rax
    pop rbx
    pop rax
    sub ax, bx
    push rax

    pop rax
    mov rbx, rbp
    sub rbx, 6
    mov word[rbx], ax

    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov rdi, printint
    xor rsi, rsi
    mov si, word[rbp-6]
    mov rax, 0
    call printf

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

    jmp .endswitch

.case3:
    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov rdi, printint
    xor rsi, rsi
    mov si, word[rbp-2]
    mov rax, 0
    call printf

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

.endswitch:
    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov rdi, printint
    xor rsi, rsi
    mov si, word[rbp-4]
    mov rax, 0
    call printf

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov rdi, printint
    xor rsi, rsi
    mov si, word[rbp-6]
    mov rax, 0
    call printf

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

    pop rsp
    pop rbp
    ret

