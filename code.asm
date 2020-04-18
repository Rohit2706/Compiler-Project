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
runtimeerror db "RUN TIME ERROR: Array index out of bounds",00h
darraysize dw 0

SECTION .text
global main
extern printf
extern scanf

main:
    call driver

    mov rax, 60
    xor rdi, rdi
    syscall

compute_expr:
    push rbp
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
    sub rsi, 9
    mov rax, 0
    call scanf

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
    sub rsi, 7
    mov rax, 0
    call scanf

    mov ax, word[rbp - -24]
    push rax
    mov ax, word[rbp - -26]
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 9]
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    pop rbx
    pop rax
    add ax, bx
    push rax

    mov rax, 3
    push rax
    pop rbx
    pop rax
    sub ax, bx
    push rax

    mov rbx, rbp
    sub rbx, 5
    pop rax
    mov word[rbx], ax

    mov ax, word[rbp - -28]
    push rax
    mov ax, word[rbp - -24]
    push rax
    mov ax, word[rbp - -26]
    push rax
    pop rbx
    pop rax
    mov rdx, 1
    cmp ax,bx
    jle label1
    mov rdx, 0
    label1:
    push rdx

    pop rbx
    pop rax
    and ax, bx
    push rax

    mov rbx, rbp
    sub rbx, 10
    pop rax
    mov byte[rbx], al

    mov ax, word[rbp - 5]
    push rax
    mov ax, word[rbp - 7]
    push rax
    pop rbx
    pop rax
    add ax, bx
    push rax

    mov rbx, rbp
    sub rbx, 2
    pop rax
    mov word[rbx], ax

    mov ax, word[rbp - 10]
    push rax
    mov ax, word[rbp - 5]
    push rax
    mov ax, word[rbp - 7]
    push rax
    pop rbx
    pop rax
    mov rdx, 1
    cmp ax,bx
    jle label2
    mov rdx, 0
    label2:
    push rdx

    pop rbx
    pop rax
    or ax, bx
    push rax

    mov rbx, rbp
    sub rbx, 3
    pop rax
    mov byte[rbx], al

    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov rdi, printint
    xor rsi, rsi
    mov si, word[rbp--24]
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
    mov si, word[rbp--26]
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

    mov rdi, formatstring
    xor rsi, rsi
    mov dl, byte[rbp--28]
    mov rsi, true
    cmp dl, 1
    je label3
    mov rsi, false
    label3:
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
    mov si, word[rbp-9]
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
    mov si, word[rbp-5]
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
    mov si, word[rbp-7]
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
    mov si, word[rbp-2]
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

    mov rdi, formatstring
    xor rsi, rsi
    mov dl, byte[rbp-3]
    mov rsi, true
    cmp dl, 1
    je label4
    mov rsi, false
    label4:
    mov rax, 0
    call printf

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

    pop rsp
    pop rbp
    pop rax
    pop rax
    push qword[rbp-2]
    push qword[rbp-3]
    push rax
    ret

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
    sub rsi, 4
    mov rax, 0
    call scanf

    mov rax, 0
    push rax
    mov rbx, rbp
    sub rbx, 8
    pop rax
    mov byte[rbx], al

    xor rbx, rbx
    mov bx, 5
    mov al, 5
    mov cl, 16
    div cl
    cmp ah, 0
    je locallabel1
    add bl, 16
    sub bl, ah
    locallabel1:

    add rsp, rbx

    mov ax, word[rbp - 2]
    mov word[rsp + 0], ax
    mov ax, word[rbp - 4]
    mov word[rsp + 2], ax
    mov al, byte[rbp - 8]
    mov byte[rsp + 4], al

    call compute_expr

    pop rax
    mov word[rbp - 6], ax
    pop rax
    mov byte[rbp - 7], al
    xor rbx, rbx
    mov bx, 5
    mov al, 5
    mov cl, 16
    div cl
    cmp ah, 0
    je locallabel2
    add bl, 16
    sub bl, ah
    locallabel2:

    sub rsp, rbx

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

    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov rdi, formatstring
    xor rsi, rsi
    mov dl, byte[rbp-7]
    mov rsi, true
    cmp dl, 1
    je label5
    mov rsi, false
    label5:
    mov rax, 0
    call printf

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

    pop rsp
    pop rbp
    ret


outofbounds:
    mov rdi, formatstring
    mov rsi, runtimeerror
    xor rax, rax
    call printf

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

    mov rax, 60
    xor rdi, rdi
    syscall

