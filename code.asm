SECTION .data
inputi  db "Input: Enter an integer value",00h
inputb  db "Input: Enter a boolean value",00h
output db "Output:",00h
formatstring db "%s"
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
formatarray db "Input: Enter %hi elements of %s type for range %hi to %hi ",0Ah,00h 
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
    sub rsp, 48
    push rbp

    mov rax, 1
    push rax
    pop rax
    mov rbx, rbp
    sub rbx, 15
    mov byte[rbx], al

    mov rax, 5
    push rax
    pop rax
    mov rbx, rbp
    sub rbx, 10
    mov word[rbx], ax

    mov rax, 9
    push rax
    pop rax
    mov rbx, rbp
    sub rbx, 12
    mov word[rbx], ax

    mov rdi, formatstring
    mov rsi, inputi
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

    mov rdi, formatint
    mov rsi, rbp
    sub rsi, 4
    mov rax, 0
    call scanf

    mov ax, word[rbp - 2]
    push rax
    mov ax, word[rbp - 4]
    push rax
    mov ax, word[rbp - 12]
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 10]
    push rax
    mov ax, word[rbp - 12]
    push rax
    pop rbx
    pop rax
    sub ax, bx
    push rax

    mov ax, word[rbp - 4]
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 10]
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 12]
    push rax
    mov ax, word[rbp - 2]
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    pop rbx
    pop rax
    sub ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
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

    mov rax, 15
    push rax
    mov rax, 10
    push rax
    mov rbx, rbp
    sub rbx, 8
    push rbx

    pop rdi
    pop rax
    mov word[rdi], ax
    push rdi
loopStart1:
    pop rax
    pop rbx
    cmp word[rax], bx
    jg loopEnd1
    push rbx
    push rax
    mov rax, 7
    push rax
    pop rax
    mov rbx, rbp
    sub rbx, 38
    mov word[rbx], ax

    mov rdi, formatstring
    mov rsi, inputi
    xor rax, rax
    call printf

    mov rdi, formatint
    mov rsi, rbp
    sub rsi, 40
    mov rax, 0
    call scanf

    mov ax, word[rbp - 38]
    push rax
    mov ax, word[rbp - 40]
    push rax
    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rax
    mov rbx, rbp
    sub rbx, 38
    mov word[rbx], ax

    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov rdi, printint
    xor rsi, rsi
    mov si, word[rbp-38]
    mov rax, 0
    call printf

    mov rdi, formatstring
    mov rsi, newline   
    xor rax, rax
    call printf

    mov ax, word[rbp - 6]
    push rax
    mov ax, word[rbp - 8]
    push rax
    mov ax, word[rbp - 38]
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

    pop rbx
    pop rax
    add ax, bx
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

    pop rax
    add word[rax],1
    push rax
    jmp loopStart1
loopEnd1:
    mov ax, word[rbp - 2]
    push rax
    mov ax, word[rbp - 4]
    push rax
    mov ax, word[rbp - 12]
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 10]
    push rax
    mov ax, word[rbp - 12]
    push rax
    pop rbx
    pop rax
    sub ax, bx
    push rax

    mov ax, word[rbp - 4]
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 10]
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov ax, word[rbp - 12]
    push rax
    mov ax, word[rbp - 2]
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    pop rbx
    pop rax
    sub ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rax
    mov rbx, rbp
    sub rbx, 6
    mov word[rbx], ax

    mov ax, word[rbp - 6]
    push rax
    mov rax, 10
    push rax
    pop rbx
    pop rax
    mov rdx, 1
    cmp ax,bx
    jg label2
    mov rdx, 0
    label2:
    push rdx

    mov ax, word[rbp - 10]
    push rax
    mov ax, word[rbp - 12]
    push rax
    pop rbx
    pop rax
    mov rdx, 1
    cmp ax,bx
    jle label3
    mov rdx, 0
    label3:
    push rdx

    mov ax, word[rbp - 2]
    push rax
    mov ax, word[rbp - 4]
    push rax
    pop rbx
    pop rax
    mov rdx, 1
    cmp ax,bx
    jl label4
    mov rdx, 0
    label4:
    push rdx

    mov ax, word[rbp - 15]
    push rax
    pop rbx
    pop rax
    and ax, bx
    push rax

    pop rbx
    pop rax
    and ax, bx
    push rax

    pop rbx
    pop rax
    or ax, bx
    push rax

    pop rax
    mov rbx, rbp
    sub rbx, 16
    mov byte[rbx], al

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
    mov dl, byte[rbp-15]
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

    mov word[range1], 10
    mov word[range2], 15

    mov qword[base], rbp
    sub qword[base], 24

    mov rdi, formatarray
    xor rsi, rsi
    mov si, word[range2]
    sub si, word[range1]
    add si, 1
    mov rdx, INTEGER
    xor rcx, rcx
    xor r8, r8
    mov cx, word[range1]
    mov r8w, word[range2]
    xor rax, rax
    call printf

    mov r15w, word[range1]
    loopStart6:
    cmp r15w, word[range2]
    jg loopEnd6

    mov rdi, formatint
    mov rsi, qword[base]
    mov rax, 0
    mov ax, r15w
    sub ax, word[range1]
    mov cx, 2
    mul cx
    sub rsi, rax
    sub rsi, 2
    mov rax, 0
    call scanf

    inc r15w
    jmp loopStart6
    loopEnd6:

    mov ax, word[rbp - 10]
    push rax
    mov ax, word[rbp - 2]
    push rax
    mov rax, 13
    push rax
    mov rbx, rbp
    sub rbx, 24
    pop rax
    sub rax, 10
    add rax, 1
    mov cx, 2
    mul cx
    sub rbx, rax
    mov ax, word[rbx]
    push rax
    mov rax, 2
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov rax, 14
    push rax
    mov rbx, rbp
    sub rbx, 24
    pop rax
    sub rax, 10
    add rax, 1
    mov cx, 2
    mul cx
    sub rbx, rax
    mov ax, word[rbx]
    push rax
    mov rax, 3
    push rax
    pop rbx
    pop rax
    imul bx
    push rax

    mov rax, 15
    push rax
    mov rbx, rbp
    sub rbx, 24
    pop rax
    sub rax, 10
    add rax, 1
    mov cx, 2
    mul cx
    sub rbx, rax
    mov ax, word[rbx]
    push rax
    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
    push rax

    pop rbx
    pop rax
    add ax, bx
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

    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov word[range1], 10
    mov word[range2], 15

    mov qword[base], rbp
    sub qword[base], 24

    mov r15w, word[range1]
    loopStart7:
    cmp r15w, word[range2]
    jg loopEnd7

    mov rdi, printint
    mov r8, qword[base]
    mov rax, 0
    mov ax, r15w
    sub ax, word[range1]
    mov cx, 2
    mul cx
    sub r8, rax
    sub r8, 2
    mov rax, 0
    xor rsi, rsi
    mov si, word[r8]
    call printf

    mov rdi, formatstring
    mov rsi, space   
    xor rax, rax
    call printf

    inc r15w
    jmp loopStart7
    loopEnd7:

    pop rsp
    pop rbp
    ret

