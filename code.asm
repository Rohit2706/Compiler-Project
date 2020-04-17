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
    sub rsp, 64
    push rbp

    mov word[range1], 6
    mov word[range2], 10

    mov qword[base], rbp
    sub qword[base], 12

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

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

    mov r15w, word[range1]
    loopStart1:
    cmp r15w, word[range2]
    jg loopEnd1

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
    jmp loopStart1
    loopEnd1:

    mov word[range1], 6
    mov word[range2], 10

    mov qword[base], rbp
    sub qword[base], 30

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

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

    mov r15w, word[range1]
    loopStart2:
    cmp r15w, word[range2]
    jg loopEnd2

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
    jmp loopStart2
    loopEnd2:

    mov rax, 10
    push rax
    mov rax, 6
    push rax
    mov rbx, rbp
    sub rbx, 2
    push rbx

    pop rdi
    pop rax
    mov word[rdi], ax
    push rdi
loopStart3:
    pop rax
    pop rbx
    cmp word[rax], bx
    jg loopEnd3
    push rbx
    push rax
    mov ax, word[rbp - 2]
    push rax
    mov r8, rbp
    sub r8, 12
    pop rax
    sub rax, 6
    add rax, 1
    mov cx, 2
    mul cx
    and rax, 0fh
    sub r8, rax
    mov ax, word[r8]
    push rax
    mov ax, word[rbp - 2]
    push rax
    mov r8, rbp
    sub r8, 30
    pop rax
    sub rax, 6
    add rax, 1
    mov cx, 2
    mul cx
    and rax, 0fh
    sub r8, rax
    mov ax, word[r8]
    push rax
    pop rbx
    pop rax
    add ax, bx
    push rax

    mov rbx, rbp
    sub rbx, 4
    pop rax
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

    mov ax, word[rbp - 4]
    push rax
    mov ax, word[rbp - 2]
    push rax
    mov r8, rbp
    sub r8, 48
    pop rax
    sub rax, 6
    add rax, 1
    mov cx, 2
    mul cx
    and rax, 0fh
    sub r8, rax
    pop rax
    mov word[r8], ax

    pop rax
    add word[rax],1
    push rax
    jmp loopStart3
loopEnd3:
    mov rdi, formatstring
    mov rsi, output
    xor rax, rax
    call printf

    mov word[range1], 6
    mov word[range2], 10

    mov qword[base], rbp
    sub qword[base], 48

    mov r15w, word[range1]
    loopStart4:
    cmp r15w, word[range2]
    jg loopEnd4

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

    inc r15w
    jmp loopStart4
    loopEnd4:

    mov rdi, formatstring
    mov rsi, newline
    xor rax, rax
    call printf

    pop rsp
    pop rbp
    ret

